#include "song.h"

Song::Song(std::string songName, int releaseYear, std::string genre, std::string audioFileName, int songId, int artistId, int albumId)
    : songName(songName),
    releaseYear(releaseYear),
    genre(genre),
    audioFilePath(audioFileName),
    songId(songId),
    artistId(artistId),
    albumId(albumId){}

std::string Song::getSongName() const {
    return this->songName;
}

int Song::getReleaseYear() const {
    return this->releaseYear;
}

std::string Song::getGenre() const {
    return this->genre;
}

std::string Song::getAudioFilePath() const {
    return this->audioFilePath;
}

int Song::getSongId() const {
    return this->songId;
}

int Song::getArtistId() const {
    return this->artistId;
}

int Song::getAlbumId() const {
    return this->albumId;
}

void Song::setSongName(const std::string& newName) {
    this->songName = newName;
}

void Song::setYear(int newYear) {
    this->releaseYear = newYear;
}

void Song::setGenre(const std::string& newGenre) {
    this->genre = newGenre;
}

void Song::setFilePath(const std::string& newName) {
    this->audioFilePath = newName;
}

void Song::setAlbumId(int newId) {
    this->albumId = newId;
}