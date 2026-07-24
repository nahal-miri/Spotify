#include "createsongdialog.h"
#include "ui_createsongdialog.h"
#include "../Repositories/songrepository.h"
#include <QFileDialog>
#include <QMessageBox>

CreateSongDialog::CreateSongDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateSongDialog)
{
    ui->setupUi(this);
}

CreateSongDialog::CreateSongDialog(std::shared_ptr<Artist> artist, std::shared_ptr<Album> album, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::CreateSongDialog),
    currentArtist(artist),
    currentAlbum(album) {
    ui->setupUi(this);
}

CreateSongDialog::~CreateSongDialog()
{
    delete ui;
}

void CreateSongDialog::on_browseButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Select Audio File", "", "Audio Files (*.mp3 *.wav)");
     if(!file.isEmpty())
        ui->audioFileLineEdit->setText(file);
}


void CreateSongDialog::on_createButton_clicked()
{
    QString songName = ui->songNameLineEdit->text();
    QString releaseYear = ui->releaseYearLineEdit->text();
    QString genre = ui->genreLineEdit->text();
    QString audioFile = ui->audioFileLineEdit->text();

    if(songName.isEmpty() || releaseYear.isEmpty() || genre.isEmpty() || audioFile.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields.");
        return;
    }

    auto song = std::make_shared<Song>(
        songName.toStdString(),
        releaseYear.toInt(),
        genre.toStdString(),
        audioFile.toStdString(),
        currentArtist->getId(),
        currentAlbum->getAlbumId());

    int result = SongRepository::getInstance().save(song);

    if(result == -1) {
        QMessageBox::warning(this, "Error", "Failed to create song.");
        return;
    }

    accept();
}

void CreateSongDialog::on_cancelButton_clicked()
{
    reject();
}

