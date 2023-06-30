#ifndef PROGRAMMER_H
#define PROGRAMMER_H
#include "people.h"

class Programmer : public People
{
public:
    Programmer(const std::string &name,const std::string &sex ,int age);
private:
    std::string gongling;
};
//如何对它读取和设置

#endif // PROGRAMMER_H
