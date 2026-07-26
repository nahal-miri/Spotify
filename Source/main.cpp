#include "mainwindow.h"
#include "../Repositories/songrepository.h"
#include "../Repositories/artistrepository.h"
#include "../Repositories/listenerrepository.h"
#include "../Repositories/playlistrepository.h"
#include "../Repositories/albumrepository.h"
#include <QApplication>
#include <QFile>
#include "../Database/database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Database::getInstance().open();
    SongRepository::getInstance().loadSongs();
    ArtistRepository::getInstance().loadArtists();
    ListenerRepository::getInstance().loadListeners();
    AlbumRepository::getInstance().loadAlbums();
    PlaylistRepository::getInstance().loadPlaylists();

    QString styleSheet = R"(
        QMainWindow {
            background-color: #E8F0FE;
        }

        QWidget {
            background-color: #E8F0FE;
            color: #1A2A3A;
            font-family: 'Segoe UI', 'Arial', sans-serif;
            font-size: 14px;
        }

        QPushButton {
            background-color: #6A9EC7;
            color: white;
            border: none;
            border-radius: 16px;
            padding: 14px 32px;
            font-size: 16px;
            font-weight: bold;
            min-width: 120px;
            min-height: 20px;
        }

        QPushButton:hover {
            background-color: #7AAED7;
        }

        QPushButton:pressed {
            background-color: #5A8AAE;
        }

        QLineEdit {
            background-color: #FFFFFF;
            border: 2px solid #C6DBEF;
            border-radius: 16px;
            padding: 14px 18px;
            color: #1A2A3A;
            font-size: 15px;
            min-height: 25px;
        }

        QLineEdit:focus {
            border-color: #6A9EC7;
            background-color: #F5F9FF;
        }

        QLineEdit::placeholder {
            color: #8AABCA;
            font-style: italic;
        }

        QLabel {
            color: #1A2A3A;
            font-size: 14px;
        }

        QLabel#titleLabel {
            font-size: 32px;
            font-weight: bold;
            color: #1A3A5C;
        }

        QLabel#subtitleLabel {
            font-size: 16px;
            font-weight: 300;
            color: #4A6A8A;
        }

        QLabel#errorLabel {
            color: #D9534F;
            font-size: 14px;
        }

        QListWidget, QTableWidget {
            background-color: #FFFFFF;
            color: #1A2A3A;
            border: 2px solid #C6DBEF;
            border-radius: 16px;
            padding: 8px;
            gridline-color: #D6E8F5;
        }

        QListWidget::item:selected, QTableWidget::item:selected {
            background-color: #C6DBEF;
            color: #1A2A3A;
        }

        QListWidget::item:hover, QTableWidget::item:hover {
            background-color: #E8F0FE;
        }

        QScrollBar:vertical {
            background-color: #E8F0FE;
            width: 12px;
            border-radius: 6px;
        }

        QScrollBar::handle:vertical {
            background-color: #C6DBEF;
            border-radius: 6px;
            min-height: 30px;
        }

        QScrollBar::handle:vertical:hover {
            background-color: #6A9EC7;
        }

        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0;
        }

        QDialog {
            background-color: #E8F0FE;
        }

        QMessageBox {
            background-color: #E8F0FE;
            color: #1A2A3A;
        }

        QMessageBox QPushButton {
            min-width: 100px;
            padding: 10px 20px;
            border-radius: 12px;
        }

        QRadioButton {
            font-size: 14px;
            font-weight: 500;
            color: #1A2A3A;
            spacing: 8px;
        }

        QRadioButton::indicator {
            width: 18px;
            height: 18px;
            border-radius: 10px;
            border: 2px solid #6A9EC7;
        }

        QRadioButton::indicator:checked {
            background-color: #6A9EC7;
            border: 2px solid #4A7A9E;
        }
    )";

    a.setStyleSheet(styleSheet);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
