#ifndef SONGREPOSITORY_H
#define SONGREPOSITORY_H
#include "AbstractRepository.h"
#include "../Entities/song.h"
#include "../Entities/artist.h"
#include <vector>
#include <optional>
#include <memory>
#include <string>

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

    int createSong(Artist& artist, const std::string& songName, int releaseYear, const std::string& genre, const std::string& audioFilePath, int albumId);
    std::vector<std::shared_ptr<Song>> searchByName(const std::vector<std::shared_ptr<Song>>& songsList, const std::string& name);
    std::vector<std::shared_ptr<Song>> filterByGenre(const std::vector<std::shared_ptr<Song>>& songsList, const std::string& genre);
    std::vector<std::shared_ptr<Song>> filterByYear(const std::vector<std::shared_ptr<Song>>& songsList, int year);
    void sortByName(std::vector<std::shared_ptr<Song>>& songs);
    void sortByYear(std::vector<std::shared_ptr<Song>>& songs);

    void loadSongs();
};

#endif // SONGREPOSITORY_H
