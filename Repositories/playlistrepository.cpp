#include "playlistrepository.h"
#include "songrepository.h"
#include <algorithm>

PlaylistRepository PlaylistRepository::instance;

PlaylistRepository::PlaylistRepository() : nextId(1) {}

PlaylistRepository& PlaylistRepository::getInstance() {
    return instance;
}

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
