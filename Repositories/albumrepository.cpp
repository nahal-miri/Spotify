#include "albumrepository.h"
#include "songrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <algorithm>

AlbumRepository  AlbumRepository::instance;

AlbumRepository::AlbumRepository() : nextId(1) {}

AlbumRepository& AlbumRepository::getInstance() {
    return instance;
}

int AlbumRepository::save(const std::shared_ptr<Album>& obj) {
    auto album = std::dynamic_pointer_cast<Album>(obj);
    if(!album)
        return -1;

    bool found = false;
    int foundInd = -1;
    if(album->getAlbumId() == 0) {
        album->setAlbumId(nextId);

        QSqlQuery query;
        query.prepare(
            "INSERT INTO albums "
            "(albumId, albumName, artistId) "
            "VALUES (?, ?, ?)"
            );

        query.addBindValue(album->getAlbumId());
        query.addBindValue(QString::fromStdString(album->getName()));
        query.addBindValue(album->getArtistId());

        if(!query.exec())
            return -1;

        nextId++;
        albums.push_back(album);

        return album->getAlbumId();
    }

    for(int i = 0; i < albums.size(); i++) {
        if(albums[i]->getAlbumId() == obj->getAlbumId()) {
            found = true;
            foundInd = i;
            break;
        }
    }

    if(found) {
        QSqlQuery query;
        query.prepare(
            "UPDATE albums SET "
            "albumName=?, "
            "artistId=? "
            "WHERE albumId=?"
            );

        query.addBindValue(QString::fromStdString(album->getName()));
        query.addBindValue(album->getArtistId());
        query.addBindValue(album->getAlbumId());

        if(!query.exec())
            return -1;

        albums[foundInd] = album;

        return album->getAlbumId();
    }

    return -1;
}

bool AlbumRepository::remove(int id) {
    auto album = search(id);
    if(!album)
        return false;

    std::vector<int> songIds;

    for (const auto& song : (*album)->getSongs()) {
        songIds.push_back(song->getSongId());
    }

    for(int songId : songIds) {
        SongRepository::getInstance().remove(songId);
    }

    QSqlQuery query;
    query.prepare("DELETE FROM albums WHERE albumId=?");
    query.addBindValue(id);

    if(!query.exec())
        return false;

    for(int i = 0; i < albums.size(); i++) {
        if(albums[i]->getAlbumId() == id) {
            albums.erase(albums.begin() + i);
            return true;
        }
    }

    return false;
}

std::optional<std::shared_ptr<Album>> AlbumRepository::search(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM albums WHERE albumId=?");
    query.addBindValue(id);

    if(!query.exec())
        return std::nullopt;

    if(!query.next())
        return std::nullopt;

    auto album = std::make_shared<Album>(
        query.value("albumName").toString().toStdString(),
        query.value("albumId").toInt(),
        query.value("artistId").toInt()
        );

    return album;
}

std::vector<std::shared_ptr<Album>> AlbumRepository::artistAlbums(int id) {

    std::vector<std::shared_ptr<Album>> result;

    for(const auto& album : albums) {
        if(album->getArtistId() == id)
            result.push_back(album);
    }

    return result;
}

int AlbumRepository::createAlbum(Artist& artist, const std::string& albumName) {
    auto album = artist.createAlbum(albumName);
    return save(album);
}

bool AlbumRepository::insertSong(int albumId, int songId) {
    auto song = SongRepository::getInstance().search(songId);
    if(!song)
        return false;

    auto album = search(albumId);
    if(!album)
        return false;

    if((*song)->getAlbumId() != 0)
        return false;

    if((*album)->getArtistId() != (*song)->getArtistId())
        return false;

    for(const auto& currentSong : (*album)->getSongs()) {
        if(currentSong->getSongId() == songId)
            return false;
    }

    (*song)->setAlbumId(albumId);
    (*album)->addSong(*song);

    return true;
}

bool AlbumRepository::removeSong(int albumId, int songId) {
    auto song = SongRepository::getInstance().search(songId);
    if(!song)
        return false;

    auto album = search(albumId);
    if(!album)
        return false;

    if((*song)->getAlbumId() != albumId)
        return false;

    (*album)->removeSong(songId);
    (*song)->setAlbumId(0);

    return true;
}

void AlbumRepository::sortByName(std::vector<std::shared_ptr<Album>>& albums) {
    std::sort(albums.begin(), albums.end(), [](const auto& a, const auto& b) {
        return a->getName() < b->getName();
    });
}

void AlbumRepository::loadAlbums() {
    albums.clear();
    QSqlQuery query("SELECT * FROM albums");

    while(query.next()) {
        auto album = std::make_shared<Album>(
            query.value("albumName").toString().toStdString(),
            query.value("albumId").toInt(),
            query.value("artistId").toInt()
            );

        albums.push_back(album);

        if(album->getAlbumId() >= nextId)
            nextId = album->getAlbumId() + 1;
    }
}
