#ifndef USER_H
#define USER_H

#include <QString>

/*
 * Это класс для авторизации.
 * С помощью него будет передаваться информация об
 * прошедшем авторизацию пользователе.
 */

class User
{
public:
    User(int i_id, QString i_login) : id(i_id), login(i_login) { }
    int getId() {return id; }
    const QString& getLogin() {return login; }
private:
    int id;
    QString login;
};

#endif // USER_H
