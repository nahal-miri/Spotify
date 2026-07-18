#ifndef SONGREPOSITORY_H
#define SONGREPOSITORY_H
#include "AbstractRepository.h"
#include "../Entities/song.h"
#include <vector>
#include <optional>

class SongRepository : public AbstractRepository<Song>
{
private:
    std::vector<std::shared_ptr<Song>> songs;
    int nextId;
    static SongRepository instance;

    SongRepository();
public:
    static SongRepository& getInstance();

    int save(const std::shared_ptr<Song>& obj) override;
    bool remove(int id) override;
    std::optional<std::shared_ptr<Song>> search(int id) override;
    std::vector<std::shared_ptr<Song>> singleSongs(int artistId);
    std::vector<std::shared_ptr<Song>> getByAlbum(int albumId);
    std::vector<std::shared_ptr<Song>> getByArtist(int artistId);
    std::vector<std::shared_ptr<Song>> getByPlaylist(int playlistId);
    std::vector<std::shared_ptr<Song>> getByLikedSongs(int listenerId);
};

#endif // SONGREPOSITORY_H
