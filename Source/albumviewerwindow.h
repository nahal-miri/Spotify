#ifndef ALBUMVIEWERWINDOW_H
#define ALBUMVIEWERWINDOW_H
#include "../Entities/artist.h"
#include "../Entities/listener.h"
#include "../Entities/album.h"
#include "../Entities/song.h"
#include <memory>
#include <qlistwidget.h>
#include <vector>
#include <QDialog>

namespace Ui {
class AlbumViewerWindow;
}

class AlbumViewerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AlbumViewerWindow(QWidget *parent = nullptr);
    explicit AlbumViewerWindow(std::shared_ptr<Artist> artist, std::shared_ptr<Listener> listener, std::shared_ptr<Album> album, QWidget *parent = nullptr);
    ~AlbumViewerWindow();

private slots:
    void on_backButton_clicked();

    void on_songsListWidget_itemClicked(QListWidgetItem *item);

    void on_likeSongButton_clicked();

    void on_addToPlayListButton_clicked();

    void on_searchSongLineEdit_textChanged(const QString &arg1);

private:
    Ui::AlbumViewerWindow *ui;
    std::shared_ptr<Artist> currentArtist;
    std::shared_ptr<Listener> currentListener;
    std::shared_ptr<Album> currentAlbum;
    std::vector<std::shared_ptr<Song>> songs;
    std::shared_ptr<Song> selectedSong;

    void loadSongs();
};

#endif // ALBUMVIEWERWINDOW_H
