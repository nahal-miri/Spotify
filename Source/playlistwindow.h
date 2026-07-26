#ifndef PLAYLISTWINDOW_H
#define PLAYLISTWINDOW_H
#include "../Entities/listener.h"
#include "../Entities/playlist.h"
#include "../Entities/song.h"
#include <QDialog>
#include <qlistwidget.h>

namespace Ui {
class PlaylistWindow;
}

class PlaylistWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PlaylistWindow(QWidget *parent = nullptr);
    explicit PlaylistWindow(std::shared_ptr<Listener> listener, std::shared_ptr<Playlist> playlist, QWidget *parent = nullptr);
    ~PlaylistWindow();

private slots:
    void on_backButton_clicked();

    void on_songsListWidget_itemClicked(QListWidgetItem *item);

    void on_removeSongButton_clicked();

    void on_searchSongLineEdit_textChanged(const QString &arg1);

private:
    Ui::PlaylistWindow *ui;
    std::shared_ptr<Listener> currentListener;
    std::shared_ptr<Playlist> currentPlaylist;
    std::vector<std::shared_ptr<Song>> songs;
     std::shared_ptr<Song> selectedSong;

    void loadSongs();
};

#endif // PLAYLISTWINDOW_H
