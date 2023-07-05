#include "programmer.h"

Programmer::Programmer(const QString &name, const QString &sex, int age)
    : People(name,sex,age)
{
    this->name = name;
    this->age = age;
    this->sex = sex;
}

void Programmer::setGongling(QString gongling)
{
    this->gongling = gongling;
}

QString Programmer::getGongling() const
{
    return this->gongling;
}
