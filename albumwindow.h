#ifndef ALBUMWINDOW_H
#define ALBUMWINDOW_H

#include <QDialog>
#include <memory>
#include "Entities/album.h"

namespace Ui {
class AlbumWindow;
}

class AlbumWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AlbumWindow(QWidget *parent = nullptr);
    explicit AlbumWindow(std::shared_ptr<Album> album, QWidget *parent = nullptr);
    ~AlbumWindow();

private:
    Ui::AlbumWindow *ui;
    std::shared_ptr<Album> currentAlbum;
};

#endif // ALBUMWINDOW_H
