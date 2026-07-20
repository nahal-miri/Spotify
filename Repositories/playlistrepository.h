#ifndef PLAYLISTREPOSITORY_H
#define PLAYLISTREPOSITORY_H
#include "AbstractRepository.h"
#include "../Entities/playlist.h"
#include "../Entities/listener.h"
#include <vector>
#include <optional>
#include <memory>
#include <string>

class PlaylistRepository : public AbstractRepository<Playlist>
{
private:
    std::vector<std::shared_ptr<Playlist>> playlists;
    int nextId;
    static PlaylistRepository instance;

    PlaylistRepository();
public:
    static PlaylistRepository& getInstance();

    int save(const std::shared_ptr<Playlist>& obj) override;
    bool remove(int id) override;
    std::optional<std::shared_ptr<Playlist>> search(int id) override;
    bool insertSong(int playlistId, int songId);
    bool removeSong(int playlistId, int songId);
    std::vector<std::shared_ptr<Playlist>> listenerPlaylists(int listenerId);

    void removeSongFromAllPlaylists(int songId);
    int createPlaylist(Listener& listener, const std::string& playlistName);
    void sortByName(std::vector<std::shared_ptr<Playlist>>& playlists);
};

#endif // PLAYLISTREPOSITORY_H
