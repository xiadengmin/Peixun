#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSqlDatabase>

#include "xdmlogtable.h"
#include <QStringList>

#include <QLineEdit>

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


private:
    Ui::XDMFrame *ui;

    XDMLogTable *m_pStuTable;
    XDMLogTable *m_pProgramTable;
private:
    QLineEdit *lineEdit_name;
    QLineEdit *lineEdit_sex;
    QLineEdit *lineEdit_age;




};



#endif // MAINWIDGET_H
