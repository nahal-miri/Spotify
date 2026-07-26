#include "createplaylistdialog.h"
#include "../Repositories/playlistrepository.h"
#include "Source/ui_createplaylistdialog.h"
#include <QMessageBox>

CreatePlaylistDialog::CreatePlaylistDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreatePlaylistDialog)
{
    ui->setupUi(this);
}

CreatePlaylistDialog::CreatePlaylistDialog(std::shared_ptr<Listener> listener, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::CreatePlaylistDialog),
    currentListener(listener) {
    ui->setupUi(this);
}

CreatePlaylistDialog::~CreatePlaylistDialog()
{
    delete ui;
}

void CreatePlaylistDialog::on_createButton_clicked()
{
    QString playlistName = ui->playlistNameLineEdit->text().trimmed();

    if(playlistName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Playlist name cannot be empty.");
        return;
    }

    auto playlist = currentListener->createPlaylist(playlistName.toStdString());
    PlaylistRepository::getInstance().save(playlist);

    accept();
}


void CreatePlaylistDialog::on_cancelButton_clicked()
{
    reject();
}

