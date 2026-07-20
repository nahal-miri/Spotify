#ifndef ALBUMREPOSITORY_H
#define ALBUMREPOSITORY_H
#include "AbstractRepository.h"
#include "../Entities/album.h"
#include "../Entities/artist.h"
#include <vector>
#include <optional>
#include <string>

class AlbumRepository : public AbstractRepository<Album>
{
private:
    std::vector<std::shared_ptr<Album>> albums;
    int nextId;
    static AlbumRepository instance;

    AlbumRepository();
public:
    static AlbumRepository& getInstance();

    int save(const std::shared_ptr<Album>& obj) override;
    bool remove(int id) override;
    std::optional<std::shared_ptr<Album>> search(int id) override;
    std::vector<std::shared_ptr<Album>> artistAlbums(int id);

    int createAlbum(Artist& artist, const std::string& albumName);
    bool insertSong(int albumId, int songId);
    bool removeSong(int albumId, int songId);
    void sortByName(std::vector<std::shared_ptr<Album>>& albums);
};

#endif // ALBUMREPOSITORY_H
