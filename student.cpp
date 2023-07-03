#include "student.h"

Student::Student(const QString &name, const QString &sex, int age)
    : People(name,sex,age)
{
    this->name = name;
    this->age = age;
    this->sex = sex;
}

void Student::setMajor(QString major)
{
    this->major = major;
}

void Student::setXuehao(QString xuehao)
{
    this->xuehao = xuehao;
}

QString Student::getMajor()
{
    return this->major;
}

QString Student::getXuehao()
{
    return this->xuehao;
}
