#include "people.h"

People::People(const std::string &name, const std::string &sex, int age) : name(name), sex(sex), age(age) {}

void People::setName(const std::string &name) {
    this->name = name;
}

std::string People::getName() const {
    return name;
}

void People::setSex(const std::string &sex) {
    this->sex = sex;
}

std::string People::getSex() const {
    return sex;
}

void People::setAge(int age) {
    this->age = age;
}

int People::getAge() const {
    return age;
}
