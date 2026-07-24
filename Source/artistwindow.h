#ifndef ARTISTWINDOW_H
#define ARTISTWINDOW_H

#include <QDialog>
#include <QListWidgetItem>
#include "../Entities/artist.h"
#include <memory>

namespace Ui {
class ArtistWindow;
}

class ArtistWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ArtistWindow(QWidget *parent = nullptr);
    explicit ArtistWindow(std::shared_ptr<Artist> artist, QWidget *parent = nullptr);
    ~ArtistWindow();

    void loadAlbums();

private slots:
    void on_newAlbumButton_clicked();

    void on_albumsListWidget_itemClicked(QListWidgetItem *item);

    void on_deleteAccountButton_clicked();

    void on_editProfileButton_clicked();

private:
    Ui::ArtistWindow *ui;
    std::shared_ptr<Artist> currentArtist;
};

#endif // ARTISTWINDOW_H
