#include "albumwindow.h"
#include "createsongdialog.h"
#include "ui_albumwindow.h"
#include "albumwindow.h"
#include "ui_albumwindow.h"
#include "albumwindow.h"
#include <QString>
#include "Repositories/songrepository.h"

AlbumWindow::AlbumWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AlbumWindow)
{
    ui->setupUi(this);
}

AlbumWindow::AlbumWindow(std::shared_ptr<Artist> artist, std::shared_ptr<Album> album, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::AlbumWindow),
    currentArtist(artist),
    currentAlbum(album) {
    ui->setupUi(this);
    ui->albumNameLabel->setText(QString::fromStdString(currentAlbum->getName()));

    loadSongs();
}

AlbumWindow::~AlbumWindow()
{
    delete ui;
}

void AlbumWindow::loadSongs() {
    ui->songsListWidget->clear();
    auto songs = SongRepository::getInstance().getByAlbum(currentAlbum->getAlbumId());

    for(const auto& song : songs)
    {
        QListWidgetItem *item =
            new QListWidgetItem(
                QString::fromStdString(song->getSongName()));

        item->setData(
            Qt::UserRole,
            song->getSongId());

        ui->songsListWidget->addItem(item);
    }
}

void AlbumWindow::on_addSongButton_clicked()
{
    CreateSongDialog dialog(currentArtist, currentAlbum);

    if(dialog.exec() == QDialog::Accepted)
        loadSongs();
}

