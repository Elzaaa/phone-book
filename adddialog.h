#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "user.h"
namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr);
    ~AddDialog();
    User getUser() const;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AddDialog *ui;
    User cUser;
};

#endif // ADDDIALOG_H
