#ifndef PROGRAMMER_H
#define PROGRAMMER_H
#include "people.h"
#include <QString>
class Programmer : public People
{
public:
    Programmer(const QString &name,const QString &sex ,int age);
    void setGongling(QString gongling);
    QString getGongling() const;
private:
    QString gongling;
};


#endif // PROGRAMMER_H
