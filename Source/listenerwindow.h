#ifndef LISTENERWINDOW_H
#define LISTENERWINDOW_H
#include "../Entities/listener.h"
#include "../Entities/artist.h"
#include "../Entities/playlist.h"
#include "../Repositories/artistrepository.h"
#include <QDialog>
#include <qlistwidget.h>

namespace Ui {
class ListenerWindow;
}

class ListenerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ListenerWindow(QWidget *parent = nullptr);
    explicit ListenerWindow(std::shared_ptr<Listener> listener, QWidget *parent = nullptr);
    ~ListenerWindow();

    void loadArtists();
    void loadPlaylists();

private slots:
    void on_artistsListWidget_itemClicked(QListWidgetItem *item);

    void on_playlistsListWidget_itemClicked(QListWidgetItem *item);

    void on_createPlaylistButton_clicked();

    void on_searchArtistLineEdit_textChanged(const QString &arg1);

    void on_removePlaylistButton_clicked();

    void on_profileButton_clicked();

private:
    Ui::ListenerWindow *ui;
    std::shared_ptr<Listener> currentListener;
    std::vector<std::shared_ptr<Artist>> artists;
    std::vector<std::shared_ptr<Playlist>> playlists;
};

#endif // LISTENERWINDOW_H
