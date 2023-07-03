#include "people.h"

People::People(const QString &name, const QString &sex, int age) : name(name), sex(sex), age(age) {}

void People::setName(const QString &name) {
    this->name = name;
}

QString People::getName() const {
    return name;
}

void People::setSex(const QString &sex) {
    this->sex = sex;
}

QString People::getSex() const {
    return sex;
}

void People::setAge(int age) {
    this->age = age;
}

int People::getAge() const {
    return age;
}
