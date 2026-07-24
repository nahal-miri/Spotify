#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H
#include "Entities/account.h"
#include <QDialog>

namespace Ui {
class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordDialog(QWidget *parent = nullptr);
    explicit ChangePasswordDialog(std::shared_ptr<Account> account, QWidget *parent = nullptr);
    ~ChangePasswordDialog();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ChangePasswordDialog *ui;
    std::shared_ptr<Account> currentAccount;
};

#endif // CHANGEPASSWORDDIALOG_H
