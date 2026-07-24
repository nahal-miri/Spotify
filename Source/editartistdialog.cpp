#include "editartistdialog.h"
#include "changepassworddialog.h"
#include "ui_editartistdialog.h"
#include "../Repositories/artistrepository.h"

EditArtistDialog::EditArtistDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditArtistDialog)
{
    ui->setupUi(this);
}

EditArtistDialog::EditArtistDialog(
    std::shared_ptr<Artist> artist,
    QWidget *parent)
    : QDialog(parent),
    ui(new Ui::EditArtistDialog),
    currentArtist(artist)
{
    ui->setupUi(this);

    ui->fullNameLineEdit->setText(
        QString::fromStdString(currentArtist->getFullName()));

    ui->userNameLineEdit->setText(
        QString::fromStdString(currentArtist->getUserName()));

    ui->bioPlainTextEdit->setPlainText(
        QString::fromStdString(currentArtist->getBio()));
}

EditArtistDialog::~EditArtistDialog()
{
    delete ui;
}

void EditArtistDialog::on_saveButton_clicked()
{
    currentArtist->setFullName(ui->fullNameLineEdit->text().toStdString());
    currentArtist->editUserName(ui->userNameLineEdit->text().toStdString());
    currentArtist->setBio(ui->bioPlainTextEdit->toPlainText().toStdString());
    ArtistRepository::getInstance().save(currentArtist);

    accept();
}


void EditArtistDialog::on_cancelButton_clicked()
{
    reject();
}


void EditArtistDialog::on_changePasswordButton_clicked()
{
    ChangePasswordDialog dialog(currentArtist);

    if(dialog.exec() == QDialog::Accepted)
        ArtistRepository::getInstance().save(currentArtist);
}

