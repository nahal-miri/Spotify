#include "album.h"

Album::Album(const std::string& albumName, int artistId)
    : albumName(albumName),
    albumId(0),
    artistId(artistId) {}

Album::Album(const std::string& albumName, int albumId, int artistId)
    : albumName(albumName),
    albumId(albumId),
    artistId(artistId) {}

std::string Album::getName() const {
    return this->albumName;
}

int Album::getAlbumId() const {
    return this->albumId;
}

int Album::getArtistId() const {
    return this->artistId;
}

const std::vector<std::shared_ptr<Song>>& Album::getSongs() const {
    return this->songs;
}
void Album::setAlbumName(const std::string& name) {
    this->albumName = name;
}

void Album::setAlbumId(int id) {
    this->albumId = id;
}

void Album::addSong(const std::shared_ptr<Song>& newSong) {
    songs.push_back(newSong);
}

void Album::removeSong(int songId) {
    for(int i = 0; i < songs.size(); i++) {
        if(songs[i]->getSongId() == songId) {
            songs.erase(songs.begin() + i);
            return;
        }
    }
}