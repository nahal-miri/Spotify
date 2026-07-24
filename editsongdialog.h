#ifndef EDITSONGDIALOG_H
#define EDITSONGDIALOG_H
#include <QDialog>
#include <memory>
#include "Entities/song.h"
#include "Entities/artist.h"

namespace Ui {
class EditSongDialog;
}

class EditSongDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditSongDialog(QWidget *parent = nullptr);
    explicit EditSongDialog(std::shared_ptr<Artist> artist, std::shared_ptr<Song> song, QWidget *parent = nullptr);
    ~EditSongDialog();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::EditSongDialog *ui;
    std::shared_ptr<Song> currentSong;
    std::shared_ptr<Artist> currentArtist;
};

#endif // EDITSONGDIALOG_H
