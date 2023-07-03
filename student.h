#ifndef STUDENT_H
#define STUDENT_H

#include "people.h"
#include <QString>
class Student : public People
{
public:
    Student(const QString &name, const QString &sex, int age);

    void setMajor(QString major);
    void setXuehao(QString xuehao);
    QString getMajor();
    QString getXuehao();
private:
    QString xuehao;
    QString major;
};


#endif // STUDENT_H
