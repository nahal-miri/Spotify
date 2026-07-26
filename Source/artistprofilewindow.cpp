#include "artistprofilewindow.h"
#include "Source/ui_artistprofilewindow.h"
#include "../Repositories/albumrepository.h"
#include "albumviewerwindow.h"

ArtistProfileWindow::ArtistProfileWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ArtistProfileWindow)
{
    ui->setupUi(this);
}

ArtistProfileWindow::ArtistProfileWindow(std::shared_ptr<Artist> artist, std::shared_ptr<Listener> listener, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::ArtistProfileWindow),
    currentArtist(artist),
    currentListener(listener) {
    ui->setupUi(this);

    ui->fullNameLabel->setText(QString::fromStdString(currentArtist->getFullName()));
    ui->userNameLabel->setText("@" + QString::fromStdString(currentArtist->getUserName()));
    ui->bioLabel->setText(QString::fromStdString(currentArtist->getBio()));

    loadAlbums();
}

ArtistProfileWindow::~ArtistProfileWindow()
{
    delete ui;
}

void ArtistProfileWindow::loadAlbums() {
    ui->albumsListWidget->clear();
    albums = AlbumRepository::getInstance().artistAlbums(currentArtist->getId());

    std::sort(albums.begin(), albums.end(), [](const auto& a, const auto& b) {
      if(a->getName() == "Singles")
          return true;

      if(b->getName() == "Singles")
          return false;

      return a->getName() < b->getName();});

    for(const auto& album : albums) {
        ui->albumsListWidget->addItem(QString::fromStdString(album->getName()));
    }
}

void ArtistProfileWindow::on_backButton_clicked()
{
    reject();
}


void ArtistProfileWindow::on_albumsListWidget_itemClicked(QListWidgetItem *item)
{
    int row = ui->albumsListWidget->row(item);
    if(row < 0 || row >= albums.size())
        return;

    auto album = albums[row];
    AlbumViewerWindow dialog(currentArtist, currentListener, album, this);

    dialog.exec();
}


void ArtistProfileWindow::on_searchAlbumLineEdit_textChanged(const QString &arg1)
{
    ui->albumsListWidget->clear();

    for(const auto &album: albums) {
        QString name = QString::fromStdString(album->getName());

        if(name.contains(arg1, Qt::CaseInsensitive))
            ui->albumsListWidget->addItem(name);
    }
}

