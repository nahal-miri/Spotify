#ifndef ALBUMWINDOW_H
#define ALBUMWINDOW_H

#include <QDialog>
#include <memory>
#include "../Entities/album.h"
#include "../Entities/artist.h"

namespace Ui {
class AlbumWindow;
}

class AlbumWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AlbumWindow(QWidget *parent = nullptr);
    explicit AlbumWindow(std::shared_ptr<Artist> artist, std::shared_ptr<Album> album, QWidget *parent = nullptr);
    ~AlbumWindow();
    void loadSongs();

private slots:
    void on_addSongButton_clicked();

    void on_editSongButton_clicked();

    void on_deleteSongButton_clicked();

    void on_editAlbumButton_clicked();

    void on_deleteButton_clicked();

    void on_backButton_clicked();

private:
    Ui::AlbumWindow *ui;
    std::shared_ptr<Album> currentAlbum;
    std::shared_ptr<Artist> currentArtist;
};

#endif // ALBUMWINDOW_H
