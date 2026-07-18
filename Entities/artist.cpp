#include "artist.h"

Artist::Artist(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password)
    : Account(fullName, userName, bio, role, password) {}

Artist::Artist(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password, int id)
    : Account(fullName, userName, bio, role, password, id) {}

void Artist::createSong(const std::string& songName, int releaseYear, const std::string& genre, const std::string& audioFilePath, int songId) {
    //complete
}