#include "albumwindow.h"
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

AlbumWindow::AlbumWindow(std::shared_ptr<Album> album, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::AlbumWindow),
    currentAlbum(album) {
    ui->setupUi(this);
    ui->albumNameLabel->setText(QString::fromStdString(currentAlbum->getName()));
    auto songs = SongRepository::getInstance().getByAlbum(currentAlbum->getAlbumId());

    for(const auto& song : songs) {
        ui->songsListWidget->addItem(QString::fromStdString(song->getSongName()));
    }
}

AlbumWindow::~AlbumWindow()
{
    delete ui;
}
