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
    Album(const std::string& albumName, int artistId);
    Album(const std::string& albumName, int albumId, int artistId);

    std::string getName() const;
    int getAlbumId() const;
    int getArtistId() const;
    const std::vector<std::shared_ptr<Song>>& getSongs() const;

    void setAlbumName(const std::string& name);
    void setAlbumId(int id);

    void addSong(const std::shared_ptr<Song>& newSong);
    void removeSong(int songId);
};

#endif // ALBUM_H
