#ifndef ALBUM_H
#define ALBUM_H
#include <string>
#include <vector>
#include <memory>
#include "song.h"

class Album
{
private:
    std::string albumName;
    int albumId;
    int artistId;
    std::vector<std::shared_ptr<Song>> songs;
public:
    Album(std::string name, int albumId, int artistId);
    std::string getName() const;
    int getAlbumId() const;
    int getArtistId() const;
    const std::vector<std::shared_ptr<Song>>& getSongs() const;
    void setName(const std::string& name);
    void addSong(const std::shared_ptr<Song>& newSong);
    void removeSong(int songId);
};

#endif // ALBUM_H
