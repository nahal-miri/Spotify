#include "artistrepository.h"

ArtistRepository ArtistRepository::instance;

ArtistRepository::ArtistRepository() : nextId(1) {}

ArtistRepository& ArtistRepository::getInstance() {
    return instance;
}

const std::vector<std::shared_ptr<Artist>>& ArtistRepository::getArtists() {
    return this->artists;
}

int ArtistRepository::save(const std::shared_ptr<Account>& obj) {
    auto artist = std::dynamic_pointer_cast<Artist>(obj);
    if(!artist)
        return -1;

    bool found = false;
    int foundInd = -1;
    if(artist->getId() == 0) {
        artist->setUserId(nextId);
        nextId++;
        artists.push_back(artist);
        return artist->getId();
    }

    for(int i = 0; i < artists.size(); i++) {
        if(artists[i]->getId() == artist->getId()) {
            found = true;
            foundInd = i;
            break;
        }
    }

    if(found) {
        artists[foundInd] = artist;
        return artist->getId();
    }

    return -1;
}

bool ArtistRepository::remove(int id) {
    for(int i = 0; i < artists.size(); i++) {
        if(artists[i]->getId() == id) {
            artists.erase(artists.begin() + i);
            return true;
        }
    }

    return false;
}

std::optional<std::shared_ptr<Account>> ArtistRepository::search(int id) {
    for(int i = 0; i < artists.size(); i++) {
        if(artists[i]->getId() == id)
            return artists[i];
    }

    return std::nullopt;
}

std::optional<std::shared_ptr<Account>> ArtistRepository::searchByUserName(const std::string& userName) {
    for(const auto& artist : artists) {
        if(artist->getUserName() == userName)
            return artist;
    }

    return std::nullopt;
}