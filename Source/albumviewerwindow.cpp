#include "albumviewerwindow.h"
#include "ui_albumviewerwindow.h"
#include "../Repositories/songrepository.h"
#include "../Repositories/listenerrepository.h"
#include "../Repositories/playlistrepository.h"
#include <QInputDialog>

AlbumViewerWindow::AlbumViewerWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AlbumViewerWindow)
{
    ui->setupUi(this);
}

AlbumViewerWindow::AlbumViewerWindow(std::shared_ptr<Artist> artist, std::shared_ptr<Listener> listener, std::shared_ptr<Album> album, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::AlbumViewerWindow),
    currentArtist(artist),
    currentListener(listener),
    currentAlbum(album) {
    ui->setupUi(this);
    ui->albumNameLabel->setText(QString::fromStdString(currentAlbum->getName()));
    ui->artistNameLabel->setText(QString::fromStdString(currentArtist->getUserName()));

    loadSongs();
}


AlbumViewerWindow::~AlbumViewerWindow()
{
    delete ui;
}

void AlbumViewerWindow::loadSongs() {
    ui->songsListWidget->clear();
    songs = SongRepository::getInstance().getByAlbum(currentAlbum->getAlbumId());

    std::sort(songs.begin(), songs.end(), [](const auto& a, const auto& b) {
        return a->getSongName() < b->getSongName();});

    for(const auto& song : songs)
    {
        ui->songsListWidget->addItem(QString::fromStdString(song->getSongName()));
    }
}

void AlbumViewerWindow::on_backButton_clicked()
{
    reject();
}

void AlbumViewerWindow::on_songsListWidget_itemClicked(QListWidgetItem *item)
{
    int row = ui->songsListWidget->row(item);

    if(row < 0 || row >= songs.size())
        return;

    selectedSong = songs[row];
}

void AlbumViewerWindow::on_likeSongButton_clicked()
{
    if(!selectedSong)
        return;

    bool liked = ListenerRepository::getInstance().isLiked(currentListener->getId(), selectedSong->getSongId());
    ListenerRepository::getInstance().updateLiked(currentListener->getId(), selectedSong->getSongId(), !liked);
    auto playlists = PlaylistRepository::getInstance().listenerPlaylists(currentListener->getId());

    for(const auto& playlist : playlists) {
        if(playlist->getPlaylistName() == "Favorite Songs") {
            if(!liked) {
                PlaylistRepository::getInstance().insertSong(playlist->getPlaylistId(), selectedSong->getSongId());
            }
            else {
                PlaylistRepository::getInstance().removeSong(playlist->getPlaylistId(), selectedSong->getSongId());
            }

            break;
        }
    }
}


void AlbumViewerWindow::on_addToPlayListButton_clicked()
{
    if(!selectedSong)
        return;

    auto playlists = PlaylistRepository::getInstance().listenerPlaylists(currentListener->getId());
    QStringList names;

    for(const auto& playlist : playlists) {
        names << QString::fromStdString(playlist->getPlaylistName());
    }

    bool ok;
    QString selected = QInputDialog::getItem(this, "Add To Playlist", "Playlist:", names, 0, false, &ok);

    if(!ok)
        return;

    for(const auto& playlist : playlists) {
        if(playlist->getPlaylistName() == selected.toStdString()) {
            PlaylistRepository::getInstance().insertSong(playlist->getPlaylistId(), selectedSong->getSongId());
            break;
        }
    }
}


void AlbumViewerWindow::on_searchSongLineEdit_textChanged(const QString &arg1)
{
    ui->songsListWidget->clear();

    for(const auto &song : songs) {
        QString name = QString::fromStdString(song->getSongName());

        if(name.contains(arg1, Qt::CaseInsensitive))
            ui->songsListWidget->addItem(name);
    }
}

