#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);
    //重置窗口大小
    resize(1300,800);
    //固定窗口大小
//    setFixedSize(1300,800);
    //设置窗口标题
    setWindowTitle("Form");
}

MainWidget::~MainWidget()
{
    delete ui;
}
