#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
}

AddDialog::~AddDialog()
{
    delete ui;
}

User AddDialog::getUser()const
{
    return cUser;
}

void AddDialog::on_pushButton_clicked()
{
    cUser.setId(ui->IdlineEdit->text());
    cUser.setFIO(ui->FIOLineEdit->text());
    cUser.setEmail(ui->EmailLineEdit->text());
    cUser.setNumber(ui->NumberLineEdit->text());
    cUser.setBday(ui->BdayLineEdit->text());
    cUser.setDay(ui->DayLineEdit->text());
    accept();
}

void AddDialog::on_pushButton_2_clicked()
{
    reject();
}



