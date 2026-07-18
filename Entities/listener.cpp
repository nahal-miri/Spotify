#include "listener.h"

Listener::Listener(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password)
    : Account(fullName, userName, bio, role, password) {}

Listener::Listener(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password, int id)
    : Account(fullName, userName, bio, role, password, id) {}

const std::vector<int>& Listener::getLikedSongsId() const {
    return this->likedSongsIds;
}

void Listener::likeSong(int songId) {
    if(!isLiked(songId))
        likedSongsIds.push_back(songId);
}

void Listener::unlikeSong(int songId) {
    for(int i = 0; i < likedSongsIds.size(); i++) {
        if(likedSongsIds[i] == songId) {
            likedSongsIds.erase(likedSongsIds.begin() + i);
            return;
        }
    }
}

bool Listener::isLiked(int songId) const {
    for(const auto& likedSong : likedSongsIds) {
        if(likedSong == songId)
            return true;
    }

    return false;
}