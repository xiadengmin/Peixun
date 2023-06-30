#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSqlDatabase>

#include <QStringList>
#include <QLineEdit>

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


private slots:
    void slotSave();
    void slotAdd();
    void slotDelet();
    void slotlineEdit_Age(const QString &arg1);
    void slotComboBoxChange(int index);
    void slotTableWidgetChange(int index);
    void getItem(const QModelIndex &index);
//    void slotUpdateHeaderList();

private:
    Ui::XDMFrame *ui;

    XDMLogTable *m_pStuTable;
    XDMLogTable *m_pProgramTable;
    XDMLogTable *g_Table;
private:
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_sex;
    QLineEdit *lineEdit_age;
    QLineEdit *lineEdit_xuehao;
    QLineEdit *lineEdit_major;
    QStringList header;

    QMap<int,QString> table1HeaderList;

};




#endif // MAINWIDGET_H
