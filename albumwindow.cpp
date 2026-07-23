#include "albumwindow.h"
#include "createsongdialog.h"
#include "editsongdialog.h"
#include "ui_albumwindow.h"
#include "albumwindow.h"
#include "ui_albumwindow.h"
#include "albumwindow.h"
#include <QString>
#include "Repositories/songrepository.h"
#include <QMessageBox>

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


void AlbumWindow::on_editSongButton_clicked()
{
    QListWidgetItem *item = ui->songsListWidget->currentItem();

    if(item == nullptr) {
        QMessageBox::warning(this, "Error", "Please select a song.");
        return;
    }

    int songId = item->data(Qt::UserRole).toInt();

    auto song = SongRepository::getInstance().search(songId);

    if(!song.has_value())
        return;

    EditSongDialog dialog(*song);

    if(dialog.exec() == QDialog::Accepted)
        loadSongs();

}


void AlbumWindow::on_deleteSongButton_clicked()
{
    QListWidgetItem *item = ui->songsListWidget->currentItem();

    if(item == nullptr) {
        QMessageBox::warning(this, "Error", "Please select a song.");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Song", "Are you sure you want to delete this song?", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No)
        return;

    int songId = item->data(Qt::UserRole).toInt();

    if(!SongRepository::getInstance().remove(songId)) {
        QMessageBox::warning(this, "Error", "Failed to delete song.");
        return;
    }

    loadSongs();
}

