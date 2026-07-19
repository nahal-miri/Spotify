#ifndef ARTIST_H
#define ARTIST_H
#include <memory>
#include "album.h"
#include "song.h"
#include "account.h"

class Artist : public Account
{
public:
    Artist(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password);
    Artist(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password, int id);

    std::shared_ptr<Album> createAlbum(const std::string& albumName);
    std::shared_ptr<Song> createSong(const std::string& songName, int releaseYear, const std::string& genre, const std::string& audioFilePath, int albumId);
};

#endif // ARTIST_H
