#ifndef EDITARTISTDIALOG_H
#define EDITARTISTDIALOG_H
#include "Entities/artist.h"
#include <QDialog>

namespace Ui {
class EditArtistDialog;
}

class EditArtistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditArtistDialog(QWidget *parent = nullptr);
    explicit EditArtistDialog(std::shared_ptr<Artist> artist, QWidget *parent = nullptr);
    ~EditArtistDialog();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

    void on_changePasswordButton_clicked();

private:
    Ui::EditArtistDialog *ui;
    std::shared_ptr<Artist> currentArtist;
};

#endif // EDITARTISTDIALOG_H
