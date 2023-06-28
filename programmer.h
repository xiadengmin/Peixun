#ifndef PROGRAMMER_H
#define PROGRAMMER_H
#include "people.h"

class Programmer : public People
{
public:
    Programmer(const std::string &name,const std::string &sex ,int age);
public:
    std::string gongLing;
};

#endif // PROGRAMMER_H
