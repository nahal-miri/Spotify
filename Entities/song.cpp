#include "song.h"

Song::Song(std::string songName, int releaseYear, std::string genre, std::string audioFilePath, int artistId, int albumId)
    : songName(songName),
    releaseYear(releaseYear),
    genre(genre),
    audioFilePath(audioFilePath),
    artistId(artistId),
    albumId(albumId),
    songId(0) {}

Song::Song(std::string songName, int releaseYear, std::string genre, std::string audioFilePath, int songId, int artistId, int albumId)
    : songName(songName),
    releaseYear(releaseYear),
    genre(genre),
    audioFilePath(audioFilePath),
    artistId(artistId),
    albumId(albumId),
    songId(songId) {}

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

void Song::setSongId(int id) {
    this->songId = id;
}

void Song::setAlbumId(int newId) {
    this->albumId = newId;
}