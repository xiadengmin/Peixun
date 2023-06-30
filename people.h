#ifndef PEOPLE_H
#define PEOPLE_H

#include <string>

class People {

public:
    People(const std::string &name, const std::string &sex, int age);

    void setName(const std::string &name);
    std::string getName() const;

    void setSex(const std::string &sex);
    std::string getSex() const;

    void setAge(int age);
    int getAge() const;
    std::string name;
    std::string sex;
    int age;

protected:


private:


};

#endif // PEOPLE_H
