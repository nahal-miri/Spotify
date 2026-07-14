#include "artist.h"

Artist::Artist(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password)
    : Account(fullName, userName, bio, role, password) {}

Artist::Artist(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password, int id)
    : Account(fullName, userName, bio, role, password, id) {}

const std::vector<std::shared_ptr<Album>>& Artist::getAlbum() const {
    return this->albums;
}

const std::vector<std::shared_ptr<Song>>& Artist::getSingleSongs() const {
    return this->singles;
}

void Artist::createAlbum(const std::string& albumName, int albumId) {
    this->albums.push_back(std::make_shared<Album>(albumName, albumId, this->userId));
}

void Artist::createSong(const std::string& songName, int releaseYear, const std::string& genre, const std::string& audioFilePath, int songId) {
    //complete
}