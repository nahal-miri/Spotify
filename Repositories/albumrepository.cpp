#include "albumrepository.h"
#include "artistrepository.h"
#include "../Entities/artist.h"

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
    auto account = ArtistRepository::getInstance().search(id);
    if(!account)
        return {};

    auto artist = std::dynamic_pointer_cast<Artist>(*account);
    if(!artist)
        return {};

    return artist->getAlbum();
}
