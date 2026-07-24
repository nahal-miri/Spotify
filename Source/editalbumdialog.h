#ifndef EDITALBUMDIALOG_H
#define EDITALBUMDIALOG_H
#include <QDialog>
#include "../Entities/album.h"

namespace Ui {
class EditAlbumDialog;
}

class EditAlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAlbumDialog(QWidget *parent = nullptr);
    EditAlbumDialog(std::shared_ptr<Album> album, QWidget *parent = nullptr);
    ~EditAlbumDialog();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::EditAlbumDialog *ui;
    std::shared_ptr<Album> currentAlbum;
};

#endif // EDITALBUMDIALOG_H
