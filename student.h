#ifndef STUDENT_H
#define STUDENT_H

#include "people.h"

class Student : public People
{
public:
    Student(const std::string &name, const std::string &sex, int age);

private:
    std::string xuehao;
    std::string major;
};


#endif // STUDENT_H
