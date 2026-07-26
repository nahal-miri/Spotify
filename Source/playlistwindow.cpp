#include "playlistwindow.h"
#include "Source/ui_playlistwindow.h"
#include "../Repositories/playlistrepository.h"
#include "../Repositories/songrepository.h"

PlaylistWindow::PlaylistWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PlaylistWindow)
{
    ui->setupUi(this);
}

PlaylistWindow::PlaylistWindow(std::shared_ptr<Listener> listener, std::shared_ptr<Playlist> playlist, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::PlaylistWindow),
    currentListener(listener),
    currentPlaylist(playlist) {
    ui->setupUi(this);
    ui->playlistNameLabel->setText(QString::fromStdString(currentPlaylist->getPlaylistName()));
    loadSongs();
}

PlaylistWindow::~PlaylistWindow()
{
    delete ui;
}

void PlaylistWindow::loadSongs() {
    ui->songsListWidget->clear();
    auto songs = SongRepository::getInstance().getByPlaylist(currentPlaylist->getPlaylistId());
    std::sort(songs.begin(), songs.end(), [](const auto& a, const auto& b) {
        return a->getSongName() < b->getSongName();});

    for(const auto& song : songs) {
        ui->songsListWidget->addItem(QString::fromStdString(song->getSongName()));
    }
}

void PlaylistWindow::on_backButton_clicked()
{
    reject();
}


void PlaylistWindow::on_songsListWidget_itemClicked(QListWidgetItem *item)
{
    int row = ui->songsListWidget->row(item);

    if(row < 0 || row >= songs.size())
        return;

    selectedSong = songs[row];
}


void PlaylistWindow::on_removeSongButton_clicked()
{
    if(!selectedSong)
        return;

    PlaylistRepository::getInstance().removeSong(
        currentPlaylist->getPlaylistId(),
        selectedSong->getSongId());

    loadSongs();

    selectedSong.reset();
}


void PlaylistWindow::on_searchSongLineEdit_textChanged(const QString &arg1)
{
    ui->songsListWidget->clear();

    for (const auto &song : songs) {
        QString name = QString::fromStdString(song->getSongName());

        if(name.contains(arg1, Qt::CaseInsensitive))
            ui->songsListWidget->addItem(name);
    }
}

