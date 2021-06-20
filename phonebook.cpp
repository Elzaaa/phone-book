#include "phonebook.h"
#include "ui_phonebook.h"

PhoneBook::PhoneBook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PhoneBook)
{
    ui->setupUi(this);
}

PhoneBook::~PhoneBook()
{
    delete ui;
}

