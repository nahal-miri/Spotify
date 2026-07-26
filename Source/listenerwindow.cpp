#include "listenerwindow.h"
#include "createplaylistdialog.h"
#include "ui_listenerwindow.h"
#include "../Repositories/artistrepository.h"
#include "../Repositories/playlistrepository.h"
#include "playlistwindow.h"
#include "artistprofilewindow.h"
#include "listenerprofilewindow.h"

ListenerWindow::ListenerWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListenerWindow)
{
    ui->setupUi(this);
}

ListenerWindow::ListenerWindow(std::shared_ptr<Listener> listener, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::ListenerWindow),
    currentListener(listener) {
    ui->setupUi(this);
    auto playlists = PlaylistRepository::getInstance().listenerPlaylists(currentListener->getId());
    bool hasFavorite = false;

    for(const auto &p : playlists) {
        if(p->getPlaylistName() == "Favorite Songs") {
            hasFavorite = true;
            break;
        }
    }

    if(!hasFavorite) {
        auto favorite = std::make_shared<Playlist>("Favorite Songs", currentListener->getId());
        PlaylistRepository::getInstance().save(favorite);
    }

    loadArtists();
    loadPlaylists();
}

ListenerWindow::~ListenerWindow()
{
    delete ui;
}

void ListenerWindow::loadArtists() {
    ui->artistsListWidget->clear();
    artists = ArtistRepository::getInstance().getArtists();
    for (const auto& artist : artists) {
        ui->artistsListWidget->addItem(QString::fromStdString(artist->getUserName()));
    }
}

void ListenerWindow::loadPlaylists() {
    ui->playlistsListWidget->clear();
    playlists = PlaylistRepository::getInstance().listenerPlaylists(currentListener->getId());
    for (const auto& playlist : playlists) {
    qDebug() << QString::fromStdString(playlist->getPlaylistName());
        ui->playlistsListWidget->addItem(QString::fromStdString(playlist->getPlaylistName()));
    }
}
void ListenerWindow::on_artistsListWidget_itemClicked(QListWidgetItem *item)
{
    if (!item)
        return;

    auto artist = ArtistRepository::getInstance().searchByUserName(item->text().toStdString());

    if (!artist)
        return;

    auto a = std::dynamic_pointer_cast<Artist>(*artist);

    if (!a)
        return;

    ArtistProfileWindow dialog(a, currentListener, this);
    dialog.exec();
}


void ListenerWindow::on_playlistsListWidget_itemClicked(QListWidgetItem *item)
{
    int row = ui->playlistsListWidget->row(item);

    if(row < 0 || row >= playlists.size())
        return;

    auto playlist = playlists[row];
    PlaylistWindow dialog(currentListener, playlist, this);

    dialog.exec();
}


void ListenerWindow::on_createPlaylistButton_clicked()
{
    CreatePlaylistDialog dialog(currentListener, this);

    if(dialog.exec() == QDialog::Accepted) {
        loadPlaylists();
    }
}


void ListenerWindow::on_searchArtistLineEdit_textChanged(const QString &arg1)
{
    ui->artistsListWidget->clear();

    for(const auto &artist : artists) {
        QString username = QString::fromStdString(artist->getUserName());
        QString fullname = QString::fromStdString(artist->getFullName());

        if(username.contains(arg1, Qt::CaseInsensitive) || fullname.contains(arg1, Qt::CaseInsensitive))
            ui->artistsListWidget->addItem(username);
    }
}

void ListenerWindow::on_removePlaylistButton_clicked()
{
    QListWidgetItem *item = ui->playlistsListWidget->currentItem();

    if (!item)
        return;

    for (const auto &playlist : playlists) {
        if (playlist->getPlaylistName() == item->text().toStdString()) {
            PlaylistRepository::getInstance().remove(playlist->getPlaylistId());
            break;
        }
    }

    loadPlaylists();
}

void ListenerWindow::on_profileButton_clicked()
{
    ListenerProfileWindow dialog(currentListener, this);
    dialog.exec();
}

