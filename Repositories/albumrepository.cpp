#include "albumrepository.h"
#include "songrepository.h"

AlbumRepository  AlbumRepository::instance;

AlbumRepository::AlbumRepository() : nextId(1) {}

AlbumRepository& AlbumRepository::getInstance() {
    return instance;
}

int AlbumRepository::save(const std::shared_ptr<Album>& obj) {
    bool found = false;
    int foundInd = -1;
    if(obj->getAlbumId() == 0) {
        obj->setAlbumID(nextId);
        nextId++;
        albums.push_back(obj);
        return obj->getAlbumId();
    }

    for(int i = 0; i < albums.size(); i++) {
        if(albums[i]->getAlbumId() == obj->getAlbumId()) {
            found = true;
            foundInd = i;
            break;
        }
    }

    if(found) {
        albums[foundInd] = obj;
        return obj->getAlbumId();
    }

    return -1;
}

bool AlbumRepository::remove(int id) {
    auto album = search(id);
    if(!album)
        return false;

    std::vector<int> songIds;

    for (const auto& song : (*album)->getSongs()) {
        songIds.push_back(song->getSongId());
    }

    for(int id : songIds) {
        SongRepository::getInstance().remove(id);
    }

    for(int i = 0; i < albums.size(); i++) {
        if(albums[i]->getAlbumId() == id) {
            albums.erase(albums.begin() + i);
            return true;
        }
    }

    return false;
}

std::optional<std::shared_ptr<Album>> AlbumRepository::search(int id) {
    for(int i = 0; i < albums.size(); i++) {
        if(albums[i]->getAlbumId() == id)
            return albums[i];
    }

    return std::nullopt;
}

std::vector<std::shared_ptr<Album>> AlbumRepository::artistAlbums(int id) {

    std::vector<std::shared_ptr<Album>> result;

    for(const auto& album : albums) {
        if(album->getArtistId() == id)
            result.push_back(album);
    }

    return result;
}

int AlbumRepository::createAlbum(Artist& artist, const std::string& albumName) {
    auto album = artist.createAlbum(albumName);
    return save(album);
}

bool AlbumRepository::insertSong(int albumId, int songId) {
    auto song = SongRepository::getInstance().search(songId);
    if(!song)
        return false;

    auto album = search(albumId);
    if(!album)
        return false;

    if((*song)->getAlbumId() != 0)
        return false;

    if((*album)->getArtistId() != (*song)->getArtistId())
        return false;

    for(const auto& currentSong : (*album)->getSongs()) {
        if(currentSong->getSongId() == songId)
            return false;
    }

    (*song)->setAlbumId(albumId);
    (*album)->addSong(*song);

    return true;
}

bool AlbumRepository::removeSong(int albumId, int songId) {
    auto song = SongRepository::getInstance().search(songId);
    if(!song)
        return false;

    auto album = search(albumId);
    if(!album)
        return false;

    if((*song)->getAlbumId() != albumId)
        return false;

    (*album)->removeSong(songId);
    (*song)->setAlbumId(0);

    return true;
}