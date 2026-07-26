#ifndef EDITPROFILEWINDOW_H
#define EDITPROFILEWINDOW_H
#include "../Entities/listener.h"
#include <QDialog>

namespace Ui {
class EditProfileWindow;
}

class EditProfileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditProfileWindow(QWidget *parent = nullptr);
    EditProfileWindow(std::shared_ptr<Listener> listener, QWidget *parent = nullptr);
    ~EditProfileWindow();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

    void on_changePasswordButton_clicked();

private:
    Ui::EditProfileWindow *ui;
    std::shared_ptr<Listener> currentListener;
};

#endif // EDITPROFILEWINDOW_H
