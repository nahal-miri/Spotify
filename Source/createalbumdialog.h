#ifndef CREATEALBUMDIALOG_H
#define CREATEALBUMDIALOG_H

#include <QDialog>
#include "../Entities/artist.h"
#include <memory>

namespace Ui {
class CreateAlbumDialog;
}

class CreateAlbumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAlbumDialog(QWidget *parent = nullptr);
    explicit CreateAlbumDialog(std::shared_ptr<Artist> artist, QWidget *parent = nullptr);
    ~CreateAlbumDialog();

private slots:
    void on_createButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::CreateAlbumDialog *ui;
    std::shared_ptr<Artist> currentArtist;
};

#endif // CREATEALBUMDIALOG_H
