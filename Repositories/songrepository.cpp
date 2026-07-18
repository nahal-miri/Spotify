#include "songrepository.h"
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
    std::vector<std::shared_ptr<Song>> albumSongs;
    for(const auto& song : songs) {
        if(song->getAlbumId() == albumId)
            albumSongs.push_back(song);
    }

    return albumSongs;
}

std::vector<std::shared_ptr<Song>> SongRepository::getByArtist(int artistId) {
    std::vector<std::shared_ptr<Song>> artistSongs;
    for(const auto& song : songs) {
        if(song->getArtistId() == artistId)
            artistSongs.push_back(song);
    }

    return artistSongs;
}

std::vector<std::shared_ptr<Song>> SongRepository::getByPlaylist(int playlistId) {
    std::vector<std::shared_ptr<Song>> playlistSongs;
    for(const auto& song : songs) {
        if(song->getArtistId() == playlistId)
            playlistSongs.push_back(song);
    }

    return playlistSongs;
}

std::vector<std::shared_ptr<Song>> SongRepository::getByLikedSongs(int listenerId) {
    auto account = ListenerRepository::getInstance().search(listenerId);
    if(!account)
        return {};

    auto listener = std::dynamic_pointer_cast<Listener>(*account);
    if(!listener)
        return {};

    std::vector<std::shared_ptr<Song>> likedSongs;

    for(int id : listener->getLikedSongsId()) {
        auto song = search(id);
        if(song)
            likedSongs.push_back(*song);
    }

    return likedSongs;
}
