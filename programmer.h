#ifndef PROGRAMMER_H
#define PROGRAMMER_H
#include "people.h"
#include <QString>
class Programmer : public People
{
public:
    Programmer(const QString &name,const QString &sex ,int age);
    void setGongling(QString gongling);
    QString getGongling();
private:
    QString gongling;
};
//如何对它读取和设置

#endif // PROGRAMMER_H
