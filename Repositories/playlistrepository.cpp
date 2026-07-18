#include "playlistrepository.h"
#include "songrepository.h"
#include "listenerrepository.h"
#include "../Entities/listener.h"

PlaylistRepository::PlaylistRepository() : nextId(1) {}

int PlaylistRepository::save(const std::shared_ptr<Playlist>& obj) {
    bool found = false;
    int foundInd = -1;
    if(obj->getPlaylistId() == 0) {
        obj->setPlaylistId(nextId);
        nextId++;
        playlists.push_back(obj);
        return obj->getPlaylistId();
    }

    for(int i = 0; i < playlists.size(); i++) {
        if(playlists[i]->getPlaylistId() == obj->getPlaylistId()) {
            found = true;
            foundInd = i;
            break;
        }
    }

    if(found) {
        playlists[foundInd] = obj;
        return obj->getPlaylistId();
    }

    return -1;
}

bool PlaylistRepository::remove(int id) {
    for(int i = 0; i < playlists.size(); i++) {
        if(playlists[i]->getPlaylistId() == id) {
            playlists.erase(playlists.begin() + i);
            return true;
        }
    }

    return false;
}

std::optional<std::shared_ptr<Playlist>> PlaylistRepository::search(int id) {
    for(const auto& playlist : playlists) {
        if(playlist->getPlaylistId() == id)
            return playlist;
    }

    return std::nullopt;
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
            (*playlist)->removeSong(songId);
            return true;
        }
    }

    return false;
}

std::vector<std::shared_ptr<Playlist>> PlaylistRepository::listenerPlaylists(int listenerId) {
    auto account = ListenerRepository::getInstance().search(listenerId);
    if(!account)
        return {};

    auto listener = std::dynamic_pointer_cast<Listener>(*account);
    if(!listener)
        return {};

    return listener->getPlaylists();
}