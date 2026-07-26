#ifndef LISTENERPROFILEWINDOW_H
#define LISTENERPROFILEWINDOW_H
#include "../Entities/listener.h"
#include <QDialog>

namespace Ui {
class ListenerProfileWindow;
}

class ListenerProfileWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ListenerProfileWindow(QWidget *parent = nullptr);
    ListenerProfileWindow(std::shared_ptr<Listener> listener, QWidget *parent = nullptr);
    ~ListenerProfileWindow();

private slots:
    void on_editProfileButton_clicked();

    void on_deleteAccountButton_clicked();

private:
    Ui::ListenerProfileWindow *ui;
    std::shared_ptr<Listener> currentListener;
};

#endif // LISTENERPROFILEWINDOW_H
