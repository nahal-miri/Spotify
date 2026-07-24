#include "songrepository.h"
#include "albumrepository.h"
#include "playlistrepository.h"
#include "listenerrepository.h"
#include "../Entities/listener.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <algorithm>

SongRepository SongRepository::instance;

SongRepository::SongRepository() : nextId(1) {}

SongRepository& SongRepository::getInstance() {
    return instance;
}

int SongRepository::save(const std::shared_ptr<Song>& obj) {
    bool found = false;
    int foundInd = -1;
    if(obj->getSongId() == 0) {
        obj->setSongId(nextId);
        QSqlQuery query;
        query.prepare(
            "INSERT INTO songs "
            "(songId, songName, releaseYear, genre, audioFilePath, artistId, albumId) "
            "VALUES (?, ?, ?, ?, ?, ?, ?)"
            );

        query.addBindValue(obj->getSongId());
        query.addBindValue(QString::fromStdString(obj->getSongName()));
        query.addBindValue(obj->getReleaseYear());
        query.addBindValue(QString::fromStdString(obj->getGenre()));
        query.addBindValue(QString::fromStdString(obj->getAudioFilePath()));
        query.addBindValue(obj->getArtistId());
        query.addBindValue(obj->getAlbumId());

        if(!query.exec()) {
            qDebug() << query.lastError().text();
            return -1;
        }

        nextId++;
        songs.push_back(obj);

        return obj->getSongId();
    }

    for(int i = 0; i < songs.size(); i++) {
        if(songs[i]->getSongId() == obj->getSongId()) {
            found = true;
            foundInd = i;
            break;
        }
    }

    if(found) {
        QSqlQuery query;
        query.prepare(
            "UPDATE songs SET "
            "songName=?, "
            "releaseYear=?, "
            "genre=?, "
            "audioFilePath=?, "
            "artistId=?, "
            "albumId=? "
            "WHERE songId=?"
            );

        query.addBindValue(QString::fromStdString(obj->getSongName()));
        query.addBindValue(obj->getReleaseYear());
        query.addBindValue(QString::fromStdString(obj->getGenre()));
        query.addBindValue(QString::fromStdString(obj->getAudioFilePath()));
        query.addBindValue(obj->getArtistId());
        query.addBindValue(obj->getAlbumId());
        query.addBindValue(obj->getSongId());

        if(!query.exec()) {
            qDebug() << query.lastError().text();
            return -1;
        }

        songs[foundInd] = obj;
        return obj->getSongId();
    }

    return -1;
}

bool SongRepository::remove(int id) {
    auto song = search(id);
    if(!song)
        return false;

    if((*song)->getAlbumId() != 0)
        AlbumRepository::getInstance().removeSong((*song)->getAlbumId(), id);

    PlaylistRepository::getInstance().removeSongFromAllPlaylists(id);
    ListenerRepository::getInstance().removeLikedSong(id);

    QSqlQuery query;
    query.prepare("DELETE FROM songs WHERE songId=?");
    query.addBindValue(id);

    if(!query.exec()) {
        qDebug() << query.lastError().text();
        return false;
    }

    for(int i = 0; i < songs.size(); i++) {
        if(songs[i]->getSongId() == id) {
            songs.erase(songs.begin() + i);
            return true;
        }
    }

    return true;
}

std::optional<std::shared_ptr<Song>> SongRepository::search(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM songs WHERE songId=?");
    query.addBindValue(id);

    if(!query.exec())
        return std::nullopt;

    if(!query.next())
        return std::nullopt;

    auto song = std::make_shared<Song>(
        query.value("songName").toString().toStdString(),
        query.value("releaseYear").toInt(),
        query.value("genre").toString().toStdString(),
        query.value("audioFilePath").toString().toStdString(),
        query.value("songId").toInt(),
        query.value("artistId").toInt(),
        query.value("albumId").toInt()
        );

    return song;
}

std::vector<std::shared_ptr<Song>> SongRepository::singleSongs(int artistId) {
    std::vector<std::shared_ptr<Song>> result;
    for(const auto& song : songs) {
        if(song->getArtistId() == artistId && song->getAlbumId() == 0)
            result.push_back(song);
    }

    return result;
}

std::vector<std::shared_ptr<Song>> SongRepository::getByAlbum(int albumId) {
    std::vector<std::shared_ptr<Song>> result;
    for(const auto& song : songs) {
        if(song->getAlbumId() == albumId)
            result.push_back(song);
    }

    return result;
}

std::vector<std::shared_ptr<Song>> SongRepository::getByArtist(int artistId) {
    std::vector<std::shared_ptr<Song>> result;
    for(const auto& song : songs) {
        if(song->getArtistId() == artistId)
            result.push_back(song);
    }

    return result;
}

std::vector<std::shared_ptr<Song>> SongRepository::getByPlaylist(int playlistId) {
    auto playlist = PlaylistRepository::getInstance().search(playlistId);
    if(!playlist)
        return {};

    return (*playlist)->getSongs();
}

std::vector<std::shared_ptr<Song>> SongRepository::getByLikedSongs(int listenerId) {
    auto account = ListenerRepository::getInstance().search(listenerId);
    if(!account)
        return {};

    auto listener = std::dynamic_pointer_cast<Listener>(*account);
    if(!listener)
        return {};

    std::vector<std::shared_ptr<Song>> result;

    for(int id : listener->getLikedSongsId()) {
        auto song = search(id);
        if(song)
            result.push_back(*song);
    }

    return result;
}

int SongRepository::createSong(Artist& artist, const std::string& songName, int releaseYear, const std::string& genre, const std::string& audioFilePath, int albumId) {
    if (albumId != 0) {
        auto album = AlbumRepository::getInstance().search(albumId);

        if (!album)
            return -1;

        if ((*album)->getArtistId() != artist.getId())
            return -1;
    }

    auto song = artist.createSong(songName, releaseYear, genre, audioFilePath, albumId);

    int songId = save(song);

    if (songId == -1)
        return -1;

    if (albumId != 0) {
        auto album = AlbumRepository::getInstance().search(albumId);
        (*album)->addSong(song);
    }

    return songId;
}

std::vector<std::shared_ptr<Song>> SongRepository::searchByName(const std::vector<std::shared_ptr<Song>>& songsList, const std::string& name) {
    std::vector<std::shared_ptr<Song>> result;

    for (const auto& song : songsList) {
        if (song->getSongName().find(name) != std::string::npos)
            result.push_back(song);
    }

    return result;
}

std::vector<std::shared_ptr<Song>> SongRepository::filterByGenre(const std::vector<std::shared_ptr<Song>>& songsList,const std::string& genre) {
    std::vector<std::shared_ptr<Song>> result;

    for (const auto& song : songsList) {
        if (song->getGenre() == genre)
            result.push_back(song);
    }

    return result;
}

std::vector<std::shared_ptr<Song>> SongRepository::filterByYear(const std::vector<std::shared_ptr<Song>>& songs, int year) {
    std::vector<std::shared_ptr<Song>> result;

    for (const auto& song : songs){
        if (song->getReleaseYear() == year)
            result.push_back(song);
    }

    return result;
}

void SongRepository::sortByName(std::vector<std::shared_ptr<Song>>& songs) {
    std::sort(songs.begin(), songs.end(), [](const auto& a, const auto& b) {
        return a->getSongName() < b->getSongName();
    });
}

void SongRepository::sortByYear(std::vector<std::shared_ptr<Song>>& songs) {
    std::sort(songs.begin(), songs.end(), [](const auto& a, const auto& b) {
        return a->getReleaseYear() < b->getReleaseYear();
    });
}

void SongRepository::loadSongs() {
    songs.clear();
    QSqlQuery query("SELECT * FROM songs");

    while(query.next()) {
        auto song = std::make_shared<Song>(
            query.value("songName").toString().toStdString(),
            query.value("releaseYear").toInt(),
            query.value("genre").toString().toStdString(),
            query.value("audioFilePath").toString().toStdString(),
            query.value("songId").toInt(),
            query.value("artistId").toInt(),
            query.value("albumId").toInt()
            );

        songs.push_back(song);

        if(song->getSongId() >= nextId)
            nextId = song->getSongId() + 1;
    }
}
