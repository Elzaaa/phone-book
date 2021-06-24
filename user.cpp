#include "user.h"

User::User(const QString &id, const QString &fio, const QString &email, const QString &number, const QString &bday, const QString &day)
{
    sId = id;
    sFIO = fio;
    sEmail = email;
    sNumber = number;
    sBday = bday;
    sDay = day;

}

void User:: setId(const QString &id)
{
    sId = id;
}
void User:: setFIO(const QString &fio)
{
    sFIO = fio;
}
void User:: setEmail(const QString &email)
{
    sEmail = email;
}
void User:: setNumber(const QString &number)
{
    sNumber = number;
}
void User:: setBday(const QString &bday)
{
    sBday = bday;
}
void User:: setDay(const QString &day)
{
    sDay = day;
}

QString User::getId() const
{
    return sId;
}
QString User::getFIO() const
{
    return sFIO;
}
QString User::getEmail() const
{
    return sEmail;
}
QString User::getNumber() const
{
    return sNumber;
}
QString User::getBday() const
{
    return sBday;
}
QString User::getDay() const
{
    return sDay;
}
