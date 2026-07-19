#include "songrepository.h"
#include "albumrepository.h"
#include "playlistrepository.h"
#include "listenerrepository.h"
#include "../Entities/listener.h"

SongRepository SongRepository::instance;

SongRepository::SongRepository() : nextId(1) {}

SongRepository& SongRepository::getInstance() {
    return instance;
}

int SongRepository::save(const std::shared_ptr<Song>& obj) {
    bool found = false;
    int foundInd = -1;
    if(obj->getSongId() == 0) {
        obj->setSongId(nextId);
        nextId++;
        songs.push_back(obj);
        return obj->getSongId();
    }

    for(int i = 0; i < songs.size(); i++) {
        if(songs[i]->getSongId() == obj->getSongId()) {
            found = true;
            foundInd = i;
            break;
        }
    }

    if(found) {
        songs[foundInd] = obj;
        return obj->getSongId();
    }

    return -1;
}

bool SongRepository::remove(int id) {
    auto song = search(id);
    if(!song)
        return false;

    if((*song)->getAlbumId() != 0)
        AlbumRepository::getInstance().removeSong((*song)->getAlbumId(), id);


    PlaylistRepository::getInstance().removeSongFromAllPlaylists(id);
    ListenerRepository::getInstance().removeLikedSong(id);

    for(int i = 0; i < songs.size(); i++) {
        if(songs[i]->getSongId() == id) {
            songs.erase(songs.begin() + i);
            return true;
        }
    }

    return false;
}

std::optional<std::shared_ptr<Song>> SongRepository::search(int id) {
    for(const auto& song : songs) {
        if(song->getSongId() == id)
            return song;
    }

    return std::nullopt;
}

std::vector<std::shared_ptr<Song>> SongRepository::singleSongs(int artistId) {
    std::vector<std::shared_ptr<Song>> result;
    for(const auto& song : songs) {
        if(song->getArtistId() == artistId && song->getAlbumId() == 0)
            result.push_back(song);
    }

    return result;
}

std::vector<std::shared_ptr<Song>> SongRepository::getByAlbum(int albumId) {
    std::vector<std::shared_ptr<Song>> result;
    for(const auto& song : songs) {
        if(song->getAlbumId() == albumId)
            result.push_back(song);
    }

    return result;
}

std::vector<std::shared_ptr<Song>> SongRepository::getByArtist(int artistId) {
    std::vector<std::shared_ptr<Song>> result;
    for(const auto& song : songs) {
        if(song->getArtistId() == artistId)
            result.push_back(song);
    }

    return result;
}

std::vector<std::shared_ptr<Song>> SongRepository::getByPlaylist(int playlistId) {
    auto playlist = PlaylistRepository::getInstance().search(playlistId);
    if(!playlist)
        return {};

    return (*playlist)->getSongs();
}

std::vector<std::shared_ptr<Song>> SongRepository::getByLikedSongs(int listenerId) {
    auto account = ListenerRepository::getInstance().search(listenerId);
    if(!account)
        return {};

    auto listener = std::dynamic_pointer_cast<Listener>(*account);
    if(!listener)
        return {};

    std::vector<std::shared_ptr<Song>> result;

    for(int id : listener->getLikedSongsId()) {
        auto song = search(id);
        if(song)
            result.push_back(*song);
    }

    return result;
}

int SongRepository::createSong(Artist& artist, const std::string& songName, int releaseYear, const std::string& genre, const std::string& audioFilePath, int albumId) {
    if (albumId != 0) {
        auto album =
            AlbumRepository::getInstance().search(albumId);

        if (!album)
            return -1;

        if ((*album)->getArtistId() != artist.getId())
            return -1;
    }

    auto song = artist.createSong(songName, releaseYear, genre, audioFilePath, albumId);

    int songId = save(song);

    if (songId == -1)
        return -1;

    if (albumId != 0) {
        auto album = AlbumRepository::getInstance().search(albumId);
        (*album)->addSong(song);
    }

    return songId;
}
