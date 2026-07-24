#include "artistwindow.h"
#include "albumwindow.h"
#include "editartistdialog.h"
#include "ui_artistwindow.h"
#include "../Repositories/albumrepository.h"
#include "../Repositories/artistrepository.h"
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

    if(dialog.exec() == QDialog::Accepted)
        loadAlbums();
}

void ArtistWindow::on_albumsListWidget_itemClicked(QListWidgetItem *item)
{

    int albumId = item->data(Qt::UserRole).toInt();
    auto album = AlbumRepository::getInstance().search(albumId);

    if(album.has_value()) {
        AlbumWindow window(currentArtist, *album);
        window.exec();
        loadAlbums();
    }
}

void ArtistWindow::on_deleteAccountButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Delete Account", "Are you sure?", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::No)
        return;

    ArtistRepository::getInstance().remove(currentArtist->getId());

    accept();
}


void ArtistWindow::on_editProfileButton_clicked()
{
    EditArtistDialog dialog(currentArtist);

    if(dialog.exec() == QDialog::Accepted) {
        ui->artistNameLabel->setText(QString::fromStdString(currentArtist->getFullName()));

        ui->artistBioLabel->setText(QString::fromStdString(currentArtist->getBio()));
    }
}

