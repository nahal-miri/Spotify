#include "artistwindow.h"
#include "albumwindow.h"
#include "ui_artistwindow.h"
#include "Repositories/albumrepository.h"
#include "createalbumdialog.h"
#include <QMessageBox>

ArtistWindow::ArtistWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ArtistWindow)
{
    ui->setupUi(this);
}

ArtistWindow::~ArtistWindow()
{
    delete ui;
}

ArtistWindow::ArtistWindow(std::shared_ptr<Artist> artist, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::ArtistWindow),
    currentArtist(artist)
{
    ui->setupUi(this);

    ui->artistNameLabel->setText(QString::fromStdString(currentArtist->getFullName()));

    ui->artistBioLabel->setText(QString::fromStdString(currentArtist->getBio()));
    loadAlbums();
}

void ArtistWindow::loadAlbums() {
    ui->albumsListWidget->clear();
    auto albums = AlbumRepository::getInstance().artistAlbums(currentArtist->getId());

    for (const auto& album : albums) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(album->getName()));
        item->setData(Qt::UserRole, album->getAlbumId());
        ui->albumsListWidget->addItem(item);
    }
}

void ArtistWindow::on_newAlbumButton_clicked()
{
    CreateAlbumDialog dialog(currentArtist);

    if(dialog.exec() == QDialog::Accepted) {
        // ui->albumsListWidget->clear();

        // auto albums = AlbumRepository::getInstance().artistAlbums(currentArtist->getId());

        // for(const auto& album : albums) {
        //     QListWidgetItem *listItem = new QListWidgetItem(QString::fromStdString(album->getName()));
        //     listItem->setData(Qt::UserRole, album->getAlbumId());
        //     ui->albumsListWidget->addItem(listItem);
        // }

        loadAlbums();
    }
}

void ArtistWindow::on_albumsListWidget_itemClicked(QListWidgetItem *item)
{

    int albumId = item->data(Qt::UserRole).toInt();
    auto album = AlbumRepository::getInstance().findById(albumId);

    if(album.has_value()) {
        AlbumWindow window(*album);
        window.exec();
    }
}
