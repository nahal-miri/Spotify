#ifndef CHANGEPASSWORDWINDOW_H
#define CHANGEPASSWORDWINDOW_H
#include "../Entities/listener.h"
#include <QDialog>

namespace Ui {
class ChangePasswordWindow;
}

class ChangePasswordWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordWindow(QWidget *parent = nullptr);
    ChangePasswordWindow(std::shared_ptr<Listener> listener, QWidget *parent = nullptr);
    ~ChangePasswordWindow();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ChangePasswordWindow *ui;
    std::shared_ptr<Listener> currentListener;
};

#endif // CHANGEPASSWORDWINDOW_H
