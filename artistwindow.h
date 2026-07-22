#ifndef ARTISTWINDOW_H
#define ARTISTWINDOW_H

#include <QDialog>
#include "Entities/artist.h"
#include <memory>

namespace Ui {
class ArtistWindow;
}

class ArtistWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ArtistWindow(QWidget *parent = nullptr);
    explicit ArtistWindow(std::shared_ptr<Artist> artist, QWidget *parent = nullptr);
    ~ArtistWindow();

private slots:
    void on_newAlbumButton_clicked();

private:
    Ui::ArtistWindow *ui;
    std::shared_ptr<Artist> currentArtist;
};

#endif // ARTISTWINDOW_H
