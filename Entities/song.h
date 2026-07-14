#ifndef SONG_H
#define SONG_H
#include <string>

class Song
{
private:
    std::string songName;
    int releaseYear;
    std::string genre;
    std::string audioFilePath;
    int songId;
    int artistId;
    int albumId;
public:
    Song(std::string songName, int releaseYear, std::string genre, std::string audioFilePath, int artistId, int albumId = 0);
    Song(std::string songName, int releaseYear, std::string genre, std::string audioFilePath, int songId, int artistId, int albumId);

    std::string getSongName() const;
    int getReleaseYear() const;
    std::string getGenre() const;
    std::string getAudioFilePath() const;
    int getSongId() const;
    int getArtistId() const;
    int getAlbumId() const;

    void setSongName(const std::string& newName);
    void setYear(int newYear);
    void setGenre(const std::string& newGenre);
    void setFilePath(const std::string& newPath);
    void setSongId(int id);
    void setAlbumId(int newId);
};

#endif // SONG_H
