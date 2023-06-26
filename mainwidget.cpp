#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);//表格设置10列
//    ui->tableWidget->setColumnWidth(0,50); //设置自定义列宽
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //x先自适应宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//根据内容使用宽度的列
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;color: black;}");//修复表头网格线丢失
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
