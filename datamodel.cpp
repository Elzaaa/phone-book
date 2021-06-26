#include "datamodel.h"
#include <QList>


DataModel::DataModel(QObject *parent) : QStandardItemModel(parent)
{
    setHorizontalHeaderLabels({"ID", "ФИО", "Email", "Телефон", "День рождения", "День внесения"});
}

void DataModel::AddUser(const User &user)
{
    QStandardItem *id = new QStandardItem(user.getId());
    QStandardItem *fio = new QStandardItem(user.getFIO());
    QStandardItem *email = new QStandardItem(user.getEmail());
    QStandardItem *number = new QStandardItem(user.getNumber());
    QStandardItem *bday = new QStandardItem(user.getBday());
    QStandardItem *day = new QStandardItem(user.getDay());

    appendRow({id, fio, email, number, bday, day});
}

QList<User> DataModel::GetUsers() const
{
    QList<User> result;

    for(int row = 0; row < rowCount(); row ++)
    {
        QStandardItem *id = item(row, 0);
        QStandardItem *fio = item(row, 1);
        QStandardItem *email = item(row,2);
        QStandardItem *number = item(row, 3);
        QStandardItem *bday = item(row, 4);
        QStandardItem *day = item(row, 5);

        User user(id->text(), fio->text(), email->text(), number->text(), bday->text(), day->text());
        result.append(user);
    }
    return result;
}
