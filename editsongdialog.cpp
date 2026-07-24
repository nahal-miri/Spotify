#include "editsongdialog.h"
#include "ui_editsongdialog.h"
#include <QMessageBox>
#include "Repositories/songrepository.h"
#include "Repositories/albumrepository.h"

EditSongDialog::EditSongDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditSongDialog)
{
    ui->setupUi(this);
}

EditSongDialog::EditSongDialog(std::shared_ptr<Artist> artist, std::shared_ptr<Song> song, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::EditSongDialog),
    currentArtist(artist),
    currentSong(song) {
    ui->setupUi(this);

    auto albums = AlbumRepository::getInstance().artistAlbums(currentArtist->getId());

    for(const auto& album : albums) {
        ui->albumComboBox->addItem(QString::fromStdString(album->getName()), album->getAlbumId());

        if(album->getAlbumId() == currentSong->getAlbumId())
            ui->albumComboBox->setCurrentIndex(ui->albumComboBox->count() - 1);
    }

    ui->songNameLineEdit->setText(QString::fromStdString(song->getSongName()));
    ui->releaseYearLineEdit->setText(QString::number(song->getReleaseYear()));
    ui->genreLineEdit->setText(QString::fromStdString(song->getGenre()));
    ui->audioFileLineEdit->setText(QString::fromStdString(song->getAudioFilePath()));
}

EditSongDialog::~EditSongDialog()
{
    delete ui;
}

void EditSongDialog::on_saveButton_clicked()
{
    QString songName = ui->songNameLineEdit->text();
    QString releaseYear = ui->releaseYearLineEdit->text();
    QString genre = ui->genreLineEdit->text();
    QString audioFile = ui->audioFileLineEdit->text();

    if(songName.isEmpty() || releaseYear.isEmpty() || genre.isEmpty() || audioFile.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields.");
        return;
    }

    int albumId = ui->albumComboBox->currentData().toInt();
    currentSong->setSongName(songName.toStdString());
    currentSong->setYear(releaseYear.toInt());
    currentSong->setGenre(genre.toStdString());
    currentSong->setFilePath(audioFile.toStdString());
    currentSong->setAlbumId(albumId);

    int result = SongRepository::getInstance().save(currentSong);

    if(result == -1) {
        QMessageBox::warning(this, "Error", "Failed to edit song.");
        return;
    }

    accept();
}


void EditSongDialog::on_cancelButton_clicked()
{
    reject();
}

