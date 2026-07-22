#include "artistwindow.h"
#include "ui_artistwindow.h"
#include "Repositories/albumrepository.h"
#include "createalbumdialog.h"

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

    auto albums = AlbumRepository::getInstance().artistAlbums(currentArtist->getId());

    for(const auto& album : albums) {
        ui->albumsListWidget->addItem(QString::fromStdString(album->getName()));
    }
}

void ArtistWindow::on_newAlbumButton_clicked()
{
    CreateAlbumDialog dialog(currentArtist);

    if(dialog.exec() == QDialog::Accepted) {
        ui->albumsListWidget->clear();

        auto albums = AlbumRepository::getInstance().artistAlbums(currentArtist->getId());

        for(const auto& album : albums) {
            ui->albumsListWidget->addItem(QString::fromStdString(album->getName()));
        }
    }
}

