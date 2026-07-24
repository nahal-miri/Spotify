#ifndef CREATESONGDIALOG_H
#define CREATESONGDIALOG_H
#include "../Entities/artist.h"
#include "../Entities/album.h"
#include <QDialog>
#include <memory>

namespace Ui {
class CreateSongDialog;
}

class CreateSongDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateSongDialog(QWidget *parent = nullptr);
    CreateSongDialog(std::shared_ptr<Artist> artist, std::shared_ptr<Album> album, QWidget *parent = nullptr);
    ~CreateSongDialog();

private slots:
    void on_browseButton_clicked();

    void on_createButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::CreateSongDialog *ui;
    std::shared_ptr<Artist> currentArtist;
    std::shared_ptr<Album> currentAlbum;
};

#endif // CREATESONGDIALOG_H
