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
    QString getMajor() const;
    QString getXuehao() const;

//    bool operator==(const Student& other) const
//    {
//        // 定义对象相等的逻辑
//        return (name == other.name && sex == other.sex && age == other.age);
//    }

//    bool operator!=(const Student& other) const
//    {
//        // 定义对象不相等的逻辑
//        return !(*this == other);
//    }

private:
    QString xuehao;
    QString major;
};




#endif // STUDENT_H
