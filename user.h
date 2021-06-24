#ifndef USER_H
#define USER_H
#include<QString>

class User
{
public:
    User(const QString &id = "", const QString &fio = "", const QString &email = "", const QString &number = "", const QString &bday = "", const QString &day = "");

    void setId(const QString &id);
    void setFIO(const QString &fio);
    void setEmail(const QString &email);
    void setNumber(const QString &number);
    void setBday(const QString &bday);
    void setDay(const QString &day);

    QString getId() const;
    QString getFIO() const;
    QString getEmail() const;
    QString getNumber() const;
    QString getBday() const;
    QString getDay() const;
private:
    QString sId;
    QString sFIO;
    QString sEmail;
    QString sNumber;
    QString sBday;
    QString sDay;

};

#endif // USER_H
