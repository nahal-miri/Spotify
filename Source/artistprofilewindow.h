#ifndef ARTISTPROFILEWINDOW_H
#define ARTISTPROFILEWINDOW_H
#include "../Entities/artist.h"
#include "../Entities/listener.h"
#include "../Entities/album.h"
#include <memory>
#include <qlistwidget.h>
#include <vector>
#include <QDialog>

namespace Ui {
class ArtistProfileWindow;
}

class ArtistProfileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ArtistProfileWindow(QWidget *parent = nullptr);
    explicit ArtistProfileWindow(std::shared_ptr<Artist> artist, std::shared_ptr<Listener> listener, QWidget *parent = nullptr);
    ~ArtistProfileWindow();

private slots:
    void on_backButton_clicked();

    void on_albumsListWidget_itemClicked(QListWidgetItem *item);

    void on_searchAlbumLineEdit_textChanged(const QString &arg1);

private:
    Ui::ArtistProfileWindow *ui;
    std::shared_ptr<Artist> currentArtist;
    std::shared_ptr<Listener> currentListener;
    std::vector<std::shared_ptr<Album>> albums;

    void loadAlbums();
};

#endif // ARTISTPROFILEWINDOW_H
