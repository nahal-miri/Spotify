#ifndef ARTIST_H
#define ARTIST_H
#include <vector>
#include <memory>
#include "album.h"
#include "song.h"
#include "account.h"

class Artist : public Account
{
public:
    Artist(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password);
    Artist(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password, int id);

    void createSong(const std::string& songName, int releaseYear, const std::string& genre, const std::string& audioFilePath, int songId);
};

#endif // ARTIST_H
