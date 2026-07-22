#include "mainwindow.h"
#include "Repositories/songrepository.h"
#include "Repositories/artistrepository.h"
#include "Repositories/listenerrepository.h"
#include "Repositories/playlistrepository.h"
#include "Repositories/albumrepository.h"
#include <QApplication>
#include "Database/database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Database::getInstance().open();
    SongRepository::getInstance().loadSongs();
    ArtistRepository::getInstance().loadArtists();
    ListenerRepository::getInstance().loadListeners();
    AlbumRepository::getInstance().loadAlbums();
    PlaylistRepository::getInstance().loadPlaylists();

    MainWindow w;
    w.show();
    return QApplication::exec();
}
