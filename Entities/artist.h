#ifndef ARTIST_H
#define ARTIST_H
#include <vector>
#include <memory>
#include "album.h"
#include "song.h"
#include "account.h"

class Artist : public Account
{
private:
    std::vector<std::shared_ptr<Album>> albums;
    std::vector<std::shared_ptr<Song>> singles;
public:
    Artist(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password);
    Artist(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password, int id);

    const std::vector<std::shared_ptr<Album>>& getAlbum() const;
    const std::vector<std::shared_ptr<Song>>& getSingleSongs() const;

    void createAlbum(const std::string& albumName, int albumId);
    void createSong(const std::string& songName, int releaseYear, const std::string& genre, const std::string& audioFilePath, int songId);
};

#endif // ARTIST_H
