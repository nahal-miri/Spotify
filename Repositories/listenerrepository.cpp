#include "listenerrepository.h"
#include "songrepository.h"
#include "playlistrepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

ListenerRepository ListenerRepository::instance;

ListenerRepository::ListenerRepository() : nextId(1) {}

ListenerRepository& ListenerRepository::getInstance() {
    return instance;
}

int ListenerRepository::save(const std::shared_ptr<Account>& obj) {
    auto listener = std::dynamic_pointer_cast<Listener>(obj);
    if(!listener)
        return -1;

    bool found = false;
    int foundInd = -1;
    if(listener->getId() == 0) {
        listener->setUserId(nextId);
        QSqlQuery query;
        query.prepare(
            "INSERT INTO listeners "
            "(listenerId, fullName, userName, bio, password) "
            "VALUES (?, ?, ?, ?, ?)"
            );

        query.addBindValue(listener->getId());
        query.addBindValue(QString::fromStdString(listener->getFullName()));
        query.addBindValue(QString::fromStdString(listener->getUserName()));
        query.addBindValue(QString::fromStdString(listener->getBio()));
        query.addBindValue(QString::fromStdString(listener->getPassword()));

        if(!query.exec())
            return -1;

        nextId++;
        listeners.push_back(listener);

        return listener->getId();
    }

    for(int i = 0; i < listeners.size(); i++) {
        if(listeners[i]->getId() == listener->getId()) {
            found = true;
            foundInd = i;
            break;
        }
    }

    if(found) {
        QSqlQuery query;
        query.prepare(
            "UPDATE listeners SET "
            "fullName=?, "
            "userName=?, "
            "bio=?, "
            "password=? "
            "WHERE listenerId=?"
            );

        query.addBindValue(QString::fromStdString(listener->getFullName()));
        query.addBindValue(QString::fromStdString(listener->getUserName()));
        query.addBindValue(QString::fromStdString(listener->getBio()));
        query.addBindValue(QString::fromStdString(listener->getPassword()));
        query.addBindValue(listener->getId());

        if(!query.exec())
            return -1;

        listeners[foundInd] = listener;

        return listener->getId();
    }

    return -1;
}

bool ListenerRepository::remove(int id) {
    auto listener = search(id);
    if(!listener)
        return false;

    auto playlists = PlaylistRepository::getInstance().listenerPlaylists(id);

    for(const auto& playlist : playlists) {
        PlaylistRepository::getInstance().remove(playlist->getPlaylistId());
    }

    QSqlQuery query;
    query.prepare("DELETE FROM listeners WHERE listenerId=?");
    query.addBindValue(id);

    if(!query.exec())
        return false;

    for(int i = 0; i < listeners.size(); i++) {
        if(listeners[i]->getId() == id) {
            listeners.erase(listeners.begin() + i);
            return true;
        }
    }

    return true;
}

std::optional<std::shared_ptr<Account>> ListenerRepository::search(int id) {
    QSqlQuery query;
    query.prepare("SELECT * FROM listeners WHERE listenerId=?");
    query.addBindValue(id);

    if(!query.exec())
        return std::nullopt;

    if(!query.next())
        return std::nullopt;

    auto listener = std::make_shared<Listener>(
        query.value("fullName").toString().toStdString(),
        query.value("userName").toString().toStdString(),
        query.value("bio").toString().toStdString(),
        query.value("password").toString().toStdString(),
        query.value("listenerId").toInt()
        );

    return listener;
}

std::optional<std::shared_ptr<Account>> ListenerRepository::searchByUserName(const std::string& userName) {
    for(const auto& listener : listeners) {
        if(listener->getUserName() == userName)
            return listener;
    }

    return std::nullopt;
}

bool ListenerRepository::updateLiked(int listenerId, int songId, bool value) {
    auto account = search(listenerId);
    if(!account)
        return false;

    auto listener = std::dynamic_pointer_cast<Listener>(*account);
    if(!listener)
        return false;

    auto song = SongRepository::getInstance().search(songId);
    if (!song)
        return false;

    if(value) {
        listener->likeSong(songId);
    }
    else {
        listener->unlikeSong(songId);
    }

    return true;
}
bool ListenerRepository::isLiked(int listenerId, int songId) {
    auto account = search(listenerId);
    if(!account)
        return false;

    auto listener = std::dynamic_pointer_cast<Listener>(*account);
    if(!listener)
        return false;

    for(const auto& likedSong : listener->getLikedSongsId()) {
        if(likedSong == songId)
            return true;
    }

    return false;
}

bool ListenerRepository::removeLikedSong(int songId) {
    for (const auto& listener : listeners) {
        listener->unlikeSong(songId);
    }

    return true;
}

void ListenerRepository::loadListeners() {
    listeners.clear();
    QSqlQuery query("SELECT * FROM listeners");

    while(query.next()) {
        auto listener = std::make_shared<Listener>(
            query.value("fullName").toString().toStdString(),
            query.value("userName").toString().toStdString(),
            query.value("bio").toString().toStdString(),
            query.value("password").toString().toStdString(),
            query.value("listenerId").toInt()
            );

        listeners.push_back(listener);

        if(listener->getId() >= nextId)
            nextId = listener->getId() + 1;
    }
}