#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include<QSqlDatabase>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
