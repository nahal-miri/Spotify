#include "playlistrepository.h"
#include "songrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <algorithm>

PlaylistRepository PlaylistRepository::instance;

PlaylistRepository::PlaylistRepository() : nextId(1) {}

PlaylistRepository& PlaylistRepository::getInstance() {
    return instance;
}

const std::vector<std::shared_ptr<Playlist>>& PlaylistRepository::getPlaylists() const {
    return playlists;
}

int PlaylistRepository::save(const std::shared_ptr<Playlist>& obj) {
    auto playlist = std::dynamic_pointer_cast<Playlist>(obj);
    if(!playlist)
        return -1;

    bool found = false;
    int foundInd = -1;
    if(obj->getPlaylistId() == 0) {
        playlist->setPlaylistId(nextId);
        QSqlQuery query;
        query.prepare(
            "INSERT INTO playlists "
            "(playlistId, playlistName, listenerId) "
            "VALUES (?, ?, ?)"
            );

        query.addBindValue(playlist->getPlaylistId());
        query.addBindValue(QString::fromStdString(playlist->getPlaylistName()));
        query.addBindValue(playlist->getListenerId());
        qDebug() << "Saving playlist:"
                 << QString::fromStdString(playlist->getPlaylistName())
                 << playlist->getListenerId();
        if(!query.exec())
            return -1;

        nextId++;
        playlists.push_back(playlist);

        return playlist->getPlaylistId();
    }

    for(int i = 0; i < playlists.size(); i++) {
        if(playlists[i]->getPlaylistId() == obj->getPlaylistId()) {
            found = true;
            foundInd = i;
            break;
        }
    }

    if(found) {
        QSqlQuery query;
        query.prepare(
            "UPDATE playlists SET "
            "playlistName=?, "
            "listenerId=? "
            "WHERE playlistId=?"
            );

        query.addBindValue(QString::fromStdString(playlist->getPlaylistName()));
        query.addBindValue(playlist->getListenerId());
        query.addBindValue(playlist->getPlaylistId());

        if(!query.exec())
            return -1;

        playlists[foundInd] = playlist;

        return playlist->getPlaylistId();
    }

    return -1;
}

bool PlaylistRepository::remove(int id) {
    QSqlQuery query;

    query.prepare("DELETE FROM playlistSongs WHERE playlistId=?");
    query.addBindValue(id);
    query.exec();

    query.prepare("DELETE FROM playlists WHERE playlistId=?");
    query.addBindValue(id);
    query.exec();

    for(int i = 0; i < playlists.size(); i++) {
        if(playlists[i]->getPlaylistId() == id) {
            playlists.erase(playlists.begin() + i);
            return true;
        }
    }

    return false;
}

std::optional<std::shared_ptr<Playlist>> PlaylistRepository::search(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM playlists WHERE playlistId=?");
    query.addBindValue(id);

    if(!query.exec())
        return std::nullopt;

    if(!query.next())
        return std::nullopt;

    auto playlist = std::make_shared<Playlist>(
        query.value("playlistName").toString().toStdString(),
        query.value("listenerId").toInt(),
        query.value("playlistId").toInt()
        );

    return playlist;
}

bool PlaylistRepository::insertSong(int playlistId, int songId) {
    auto playlist = search(playlistId);
    if(!playlist)
        return false;

    auto song = SongRepository::getInstance().search(songId);
    if(!song)
        return false;

    for(const auto& currentSong : (*playlist)->getSongs()) {
        if(currentSong->getSongId() == songId)
            return false;
    }

    QSqlQuery query;
    query.prepare(
        "INSERT INTO playlistSongs "
        "(playlistId, songId) "
        "VALUES (?, ?)"
        );

    query.addBindValue(playlistId);
    query.addBindValue(songId);

    if(!query.exec())
        return false;

    (*playlist)->addSong(*song);
    return true;
}

bool PlaylistRepository::removeSong(int playlistId, int songId) {
    auto playlist = search(playlistId);
    if(!playlist)
        return false;

    auto song = SongRepository::getInstance().search(songId);
    if(!song)
        return false;

    for(const auto& currentSong : (*playlist)->getSongs()) {
        if(currentSong->getSongId() == songId) {
            QSqlQuery query;
            query.prepare(
                "DELETE FROM playlistSongs "
                "WHERE playlistId=? AND songId=?"
                );

            query.addBindValue(playlistId);
            query.addBindValue(songId);

            if(!query.exec())
                return false;
            (*playlist)->removeSong(songId);
            return true;
        }
    }

    return false;
}

std::vector<std::shared_ptr<Playlist>> PlaylistRepository::listenerPlaylists(int listenerId) {
    std::vector<std::shared_ptr<Playlist>> result;

    for(const auto& playlist : playlists) {
        if(playlist->getListenerId() == listenerId)
            result.push_back(playlist);
    }

    return result;
}

void PlaylistRepository::removeSongFromAllPlaylists(int songId) {
    for (const auto& playlist : playlists) {
        playlist->removeSong(songId);
        QSqlQuery query;
        query.prepare("DELETE FROM playlistSongs WHERE songId=?");
        query.addBindValue(songId);
        query.exec();
    }
}

int PlaylistRepository::createPlaylist(Listener& listener, const std::string& playlistName) {
    auto playlist = listener.createPlaylist(playlistName);
    return save(playlist);
}

void PlaylistRepository::sortByName(std::vector<std::shared_ptr<Playlist>>& playlists) {
    std::sort(playlists.begin(), playlists.end(), [](const auto& a, const auto& b) {
        return a->getPlaylistName() < b->getPlaylistName();
    });
}

void PlaylistRepository::loadPlaylists() {
    playlists.clear();
    QSqlQuery query("SELECT * FROM playlists");

    while(query.next()) {
        auto playlist = std::make_shared<Playlist>(
            query.value("playlistName").toString().toStdString(),
            query.value("listenerId").toInt(),
            query.value("playlistId").toInt()
            );

        QSqlQuery songQuery;
        songQuery.prepare("SELECT songId FROM playlistSongs WHERE playlistId=?");
        songQuery.addBindValue(playlist->getPlaylistId());
        songQuery.exec();

        while(songQuery.next()) {
            auto song = SongRepository::getInstance().search(songQuery.value(0).toInt());

            if(song)
                playlist->addSong(*song);
        }

        playlists.push_back(playlist);

        if(playlist->getPlaylistId() >= nextId)
            nextId = playlist->getPlaylistId() + 1;
    }
}
