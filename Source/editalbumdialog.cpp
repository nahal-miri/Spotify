#include "editalbumdialog.h"
#include "ui_editalbumdialog.h"
#include <QMessageBox>
#include "../Repositories/albumrepository.h"

EditAlbumDialog::EditAlbumDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditAlbumDialog)
{
    ui->setupUi(this);
}

EditAlbumDialog::EditAlbumDialog(std::shared_ptr<Album> album, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::EditAlbumDialog),
    currentAlbum(album) {
    ui->setupUi(this);
    ui->albumNameLineEdit->setText(QString::fromStdString(currentAlbum->getName()));
}

EditAlbumDialog::~EditAlbumDialog()
{
    delete ui;
}

void EditAlbumDialog::on_saveButton_clicked()
{
    QString name = ui->albumNameLineEdit->text();

    if(name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Album name cannot be empty.");
        return;
    }

    currentAlbum->setAlbumName(name.toStdString());

    if(AlbumRepository::getInstance().save(currentAlbum) == -1) {
        QMessageBox::warning(this, "Error", "Failed to edit album.");
        return;
    }

    accept();
}


void EditAlbumDialog::on_cancelButton_clicked()
{
    reject();
}

