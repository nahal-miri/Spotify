#ifndef LISTENER_H
#define LISTENER_H
#include <vector>
#include <string>
#include <memory>
#include "account.h"
#include "playlist.h"

class Listener : public Account
{
private:
    std::vector<std::shared_ptr<Playlist>> playlists;
    std::vector<int> likedSongsIds;
public:
    Listener(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password);
    Listener(const std::string& fullName, const std::string& userName, const std::string& bio, Role role, const std::string& password, int id);

    const std::vector<std::shared_ptr<Playlist>>& getPlaylists() const;
    const std::vector<int>& getLikedSongsId() const;

    void addPlaylist(const std::shared_ptr<Playlist>& playlist);
    void removePLaylist(int playlistId);

    void likeSong(int songId);
    void unlikeSong(int songId);
    bool isLiked(int songId) const;
};

#endif // LISTENER_H
