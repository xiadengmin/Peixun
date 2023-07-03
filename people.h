#ifndef PEOPLE_H
#define PEOPLE_H

#include <QString>

class People {

public:
    People(const QString &name, const QString &sex, int age);

    void setName(const QString &name);
    QString getName() const;

    void setSex(const QString &sex);
    QString getSex() const;

    void setAge(int age);
    int getAge() const;

    QString name;
    QString sex;
    int age;

protected:


private:


};

#endif // PEOPLE_H
