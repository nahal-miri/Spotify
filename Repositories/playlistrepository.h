#ifndef PLAYLISTREPOSITORY_H
#define PLAYLISTREPOSITORY_H
#include "AbstractRepository.h"
#include "../Entities/playlist.h"
#include <vector>
#include <optional>

class PlaylistRepository : public AbstractRepository<Playlist>
{
private:
    std::vector<std::shared_ptr<Playlist>> playlists;
    int nextId;
public:
    PlaylistRepository();

    int save(const std::shared_ptr<Playlist>& obj) override;
    bool remove(int id) override;
    std::optional<std::shared_ptr<Playlist>> search(int id) override;
    bool insertSong(int playlistId, int songId);
    bool removeSong(int playlistId, int songId);
    std::vector<std::shared_ptr<Playlist>> listenerPlaylists(int listenerId);
};

#endif // PLAYLISTREPOSITORY_H
