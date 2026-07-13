#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <string>
#include <vector>
#include <memory>
#include "song.h"

class Playlist
{
private:
    std::string playlistName;
    int listenerId;
    int playlistId;
    std::vector<std::shared_ptr<Song>> songs;
public:
    Playlist(std::string playlistName, int listenerId, int playlistId);

    std::string getPlaylistName() const;
    int getListenerId() const;
    int getPlaylistId() const;
    const std::vector<std::shared_ptr<Song>>& getSongs() const;

    void setPlaylistName(const std::string& newName);

    void addSong(const std::shared_ptr<Song>& newSong);
    void removeSong(int songId);
};

#endif // PLAYLIST_H
