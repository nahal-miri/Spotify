#include "editsongdialog.h"
#include "ui_editsongdialog.h"
#include <QMessageBox>
#include "Repositories/songrepository.h"

EditSongDialog::EditSongDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditSongDialog)
{
    ui->setupUi(this);
}

EditSongDialog::EditSongDialog(std::shared_ptr<Song> song, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::EditSongDialog),
    currentSong(song) {
    ui->setupUi(this);

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

    currentSong->setSongName(songName.toStdString());
    currentSong->setYear(releaseYear.toInt());
    currentSong->setGenre(genre.toStdString());
    currentSong->setFilePath(audioFile.toStdString());

    int result = SongRepository::getInstance().save(currentSong);

    if(result == -1) {
        QMessageBox::warning(this, "Error", "Failed to edit song.");
        return;
    }

    accept();
}

