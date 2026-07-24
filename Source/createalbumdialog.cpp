#include "createalbumdialog.h"
#include "ui_createalbumdialog.h"
#include <QMessageBox>
#include "../Repositories/albumrepository.h"
#include "../Entities/album.h"

CreateAlbumDialog::CreateAlbumDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateAlbumDialog)
{
    ui->setupUi(this);
}

CreateAlbumDialog::~CreateAlbumDialog()
{
    delete ui;
}

CreateAlbumDialog::CreateAlbumDialog(std::shared_ptr<Artist> artist, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::CreateAlbumDialog),
    currentArtist(artist) {
    ui->setupUi(this);
}

void CreateAlbumDialog::on_createButton_clicked()
{
    QString name = ui->albumNameLineEdit->text();

    if(name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Album name cannot be empty.");
        return;
    }

    auto album = std::make_shared<Album>(name.toStdString(),  currentArtist->getId());

    AlbumRepository::getInstance().save(album);

    accept();
}


void CreateAlbumDialog::on_cancelButton_clicked()
{
    reject();
}

