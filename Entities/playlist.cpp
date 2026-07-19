#include "playlist.h"

Playlist::Playlist(const std::string& playlistName, int listenerId)
    : playlistName(playlistName),
    listenerId(listenerId),
    playlistId(0) {}

Playlist::Playlist(const std::string& playlistName, int listenerId, int playlistId)
    : playlistName(playlistName),
    listenerId(listenerId),
    playlistId(playlistId) {}

std::string Playlist::getPlaylistName() const {
    return this->playlistName;
}

int Playlist::getListenerId() const {
    return this->listenerId;
}

int Playlist::getPlaylistId() const {
    return this->playlistId;
}

const std::vector<std::shared_ptr<Song>>& Playlist::getSongs() const {
    return this->songs;
}

void Playlist::setPlaylistName(const std::string& newName) {
    this->playlistName = newName;
}

void Playlist::setPlaylistId(int id) {
    this->playlistId = id;
}

void Playlist::addSong(const std::shared_ptr<Song>& newSong) {
    songs.push_back(newSong);
}

void Playlist::removeSong(int songId) {
    for(int i = 0; i < songs.size(); i++) {
        if(songs[i]->getSongId() == songId) {
            songs.erase(songs.begin() + i);
            return;
        }
    }
}