#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QStandardItemModel>
#include <QObject>
#include "user.h"

class DataModel : public QStandardItemModel
{
        Q_OBJECT
public:
     DataModel(QObject *parent);
     void AddUser(const User &user);
     QList <User> GetUsers() const;

};

#endif // DATAMODEL_H
