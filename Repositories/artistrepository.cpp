#include "artistrepository.h"
#include "albumrepository.h"
#include "songrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <memory>

ArtistRepository ArtistRepository::instance;

ArtistRepository::ArtistRepository() : nextId(1) {}

ArtistRepository& ArtistRepository::getInstance() {
    return instance;
}

const std::vector<std::shared_ptr<Artist>>& ArtistRepository::getArtists() const {
    return this->artists;
}

int ArtistRepository::save(const std::shared_ptr<Account>& obj) {
    auto artist = std::dynamic_pointer_cast<Artist>(obj);
    if(!artist)
        return -1;

    bool found = false;
    int foundInd = -1;
    if(artist->getId() == 0) {
        artist->setUserId(nextId);
        QSqlQuery query;
        query.prepare(
            "INSERT INTO artists "
            "(artistId, fullName, userName, bio, password) "
            "VALUES (?, ?, ?, ?, ?)"
            );

        query.addBindValue(artist->getId());
        query.addBindValue(QString::fromStdString(artist->getFullName()));
        query.addBindValue(QString::fromStdString(artist->getUserName()));
        query.addBindValue(QString::fromStdString(artist->getBio()));
        query.addBindValue(QString::fromStdString(artist->getPassword()));

        if(!query.exec())
            return -1;

        nextId++;
        artists.push_back(artist);
        auto singles = std::make_shared<Album>("Singles", artist->getId());
        AlbumRepository::getInstance().save(singles);

        return artist->getId();
    }

    for(int i = 0; i < artists.size(); i++) {
        if(artists[i]->getId() == artist->getId()) {
            found = true;
            foundInd = i;
            break;
        }
    }

    if(found) {
        QSqlQuery query;
        query.prepare(
            "UPDATE artists SET "
            "fullName=?, "
            "userName=?, "
            "bio=?, "
            "password=? "
            "WHERE artistId=?"
            );

        query.addBindValue(QString::fromStdString(artist->getFullName()));
        query.addBindValue(QString::fromStdString(artist->getUserName()));
        query.addBindValue(QString::fromStdString(artist->getBio()));
        query.addBindValue(QString::fromStdString(artist->getPassword()));
        query.addBindValue(artist->getId());

        if(!query.exec())
            return -1;

        artists[foundInd] = artist;

        return artist->getId();
    }

    return -1;
}

bool ArtistRepository::remove(int id) {
    auto artist = search(id);
    if(!artist)
        return false;

    auto songs = SongRepository::getInstance().getByArtist(id);

    QSqlQuery query;
    query.prepare("DELETE FROM artists WHERE artistId=?");
    query.addBindValue(id);

    if(!query.exec())
        return false;

    for(const auto& song : songs) {
        if(song->getAlbumId() == 0) {
            SongRepository::getInstance().remove(song->getSongId());
        }
    }


    auto albums = AlbumRepository::getInstance().artistAlbums(id);

    for(const auto& album : albums) {
        AlbumRepository::getInstance().remove(album->getAlbumId());
    }

    for(int i = 0; i < artists.size(); i++) {
        if(artists[i]->getId() == id) {
            artists.erase(artists.begin() + i);
            return true;
        }
    }

    return true;
}

std::optional<std::shared_ptr<Account>> ArtistRepository::search(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM artists WHERE artistId=?");
    query.addBindValue(id);

    if(!query.exec())
        return std::nullopt;

    if(!query.next())
        return std::nullopt;

    auto artist = std::make_shared<Artist>(
        query.value("fullName").toString().toStdString(),
        query.value("userName").toString().toStdString(),
        query.value("bio").toString().toStdString(),
        query.value("password").toString().toStdString(),
        query.value("artistId").toInt()
        );

    return artist;
}

std::optional<std::shared_ptr<Account>> ArtistRepository::searchByUserName(const std::string& userName) {
    for(const auto& artist : artists) {
        if(artist->getUserName() == userName)
            return artist;
    }

    return std::nullopt;
}

void ArtistRepository::loadArtists() {
    artists.clear();
    QSqlQuery query("SELECT * FROM artists");

    while(query.next()) {
        auto artist = std::make_shared<Artist>(
            query.value("fullName").toString().toStdString(),
            query.value("userName").toString().toStdString(),
            query.value("bio").toString().toStdString(),
            query.value("password").toString().toStdString(),
            query.value("artistId").toInt()
            );

        artists.push_back(artist);

        if(artist->getId() >= nextId)
            nextId = artist->getId() + 1;
    }
}