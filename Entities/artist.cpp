#include "artist.h"

Artist::Artist(const std::string& fullName, const std::string& userName, const std::string& bio, const std::string& password)
    : Account(fullName, userName, bio, Role::Artist, password) {}

Artist::Artist(const std::string& fullName, const std::string& userName, const std::string& bio, const std::string& password, int id)
    : Account(fullName, userName, bio, Role::Artist, password, id) {}

std::shared_ptr<Album> Artist::createAlbum(const std::string& albumName) {
    return std::make_shared<Album>(albumName, this->userId);
}

std::shared_ptr<Song> Artist::createSong(const std::string& songName, int releaseYear, const std::string& genre, const std::string& audioFilePath, int albumId) {
    return std::make_shared<Song>(songName, releaseYear, genre, audioFilePath, this->getId(), albumId);
}