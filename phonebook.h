#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class PhoneBook; }
QT_END_NAMESPACE

class PhoneBook : public QMainWindow
{
    Q_OBJECT

public:
    PhoneBook(QWidget *parent = nullptr);
    ~PhoneBook();

private:
    Ui::PhoneBook *ui;
};
#endif // PHONEBOOK_H
