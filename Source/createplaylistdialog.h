#ifndef CREATEPLAYLISTDIALOG_H
#define CREATEPLAYLISTDIALOG_H
#include "../Entities/listener.h"
#include <QDialog>

namespace Ui {
class CreatePlaylistDialog;
}

class CreatePlaylistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreatePlaylistDialog(QWidget *parent = nullptr);
    explicit CreatePlaylistDialog(std::shared_ptr<Listener> listener, QWidget *parent = nullptr);
    ~CreatePlaylistDialog();

private slots:
    void on_createButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::CreatePlaylistDialog *ui;
    std::shared_ptr<Listener> currentListener;
};

#endif // CREATEPLAYLISTDIALOG_H
