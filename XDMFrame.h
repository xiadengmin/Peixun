#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSqlDatabase>

#include <QStringList>
#include <QLineEdit>
#include <QList>
#include "xdmlogtable.h"
#include "student.h"
#include "programmer.h"

namespace Ui {
class XDMFrame;
}

class XDMFrame : public QWidget
{
    Q_OBJECT

public:
    explicit XDMFrame(QWidget *parent = 0);
    ~XDMFrame();

    void lineEditClear();
    void updateCur();

private slots:
    void slotSave();
    void slotAdd();
    void slotDelete();
    void slotlineEdit_Age(const QString &arg1);
    void slotComboBoxChange(int index);
    void slotTableWidgetChange(int index);

    void slotHomePage();
    void slotPageUp();
    void slotPageDown();
    void slotLastPage();
    void slotRedirect();

    void slotlineEdit(QStringList sl);


//    void getItem(const QModelIndex &index);     引用和指针的区别
//    void slotUpdateHeaderList();

private:
    Ui::XDMFrame *ui;

    XDMLogTable *m_pStuTable;
    XDMLogTable *m_pProgramTable;
    XDMLogTable *g_Table;

    QList<Student> s_list;
    QList<Programmer> p_list;
    int currentPage_1 = 1;  // 当前页码，初始化为1
    int currentPage_2 = 1;
    int allPage_1;
    int allPage_2;

private:

    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_sex;
    QLineEdit *lineEdit_age;
    QLineEdit *lineEdit_xuehao;
    QLineEdit *lineEdit_major;
    QStringList header;

    QMap<int,QString> table1HeaderList_stu;
    QMap<int,QString> table1HeaderList_pro;



};




#endif // MAINWIDGET_H
