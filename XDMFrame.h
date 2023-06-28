#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QSqlDatabase>

#include "xdmlogtable.h"
#include <QStringList>

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

    void on_pushButton_Add_clicked();

    void on_pushButton_Open_clicked();

private:
    Ui::XDMFrame *ui;

    XDMLogTable *m_pStuTable;
    XDMLogTable *m_pProgramTable;
};

#endif // MAINWIDGET_H
