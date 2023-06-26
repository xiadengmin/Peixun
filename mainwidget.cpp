#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QCheckBox>

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QApplication>

#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    //表格设置
//    ui->tableWidget->setRowCount(10);//表格设置10列
//    ui->tableWidget->setColumnWidth(0,50); //设置自定义列宽
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //x先自适应宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//根据内容使用宽度的列
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;color: black;}");//修复表头网格线丢失

//    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑

    // 遍历每一行 使用checkBoxItem 设置复选框
    for(int i = 0; i < 10; i++)
    {
        QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
        checkBoxItem->setCheckState(Qt::Unchecked); // 默认设为未选中
        ui->tableWidget->setItem(i, 0, checkBoxItem); // 在第一列添加复选框
    }


    //重置窗口大小
    resize(1300,800);
    //固定窗口大小
//    setFixedSize(1300,800);
    //设置窗口标题
    setWindowTitle("Form");
}



//combobox和tablewidget 关联
//逻辑： 在槽函数内 进行两次 判断当前tabWidget活动标签页和comboBox活动标签页是否一致 来关联两个标签
void MainWidget::on_comboBox_currentIndexChanged(int index)
{
    if(ui->comboBox->currentIndex()==0)
    {
        ui->tabWidget->setCurrentIndex(0);
        ui->label_6->setText("学 号：");//重命名学号
        ui->label_5->setVisible(true);
        ui->textEdit_5->setVisible(true);//重显示专业
        QStringList strs = {"        序号        ","        姓名        ", "        性别        ", "        年龄        ", "       学号        ", "      专业      "};
        ui->tableWidget->setHorizontalHeaderLabels(strs); //学生表头
        ui->tableWidget->setColumnHidden(5, false); // 显示第6列专业
    }
    else
    {
        ui->tabWidget->setCurrentIndex(1);
        ui->label_6->setText("工 龄：");//程序员工龄
        ui->label_5->setVisible(false);
        ui->textEdit_5->setVisible(false);//隐藏专业
        QStringList strs = {"        序号        ","        姓名        ", "        性别        ", "        年龄        ", "       工龄        ", "      专业      "};
        ui->tableWidget->setHorizontalHeaderLabels(strs);//程序员表头
        ui->tableWidget->setColumnHidden(5, true); // 隐藏第6列专业

    }
//    ui->tabWidget->setCurrentIndex(0); // 设置当前tabWidget活动标签页第1页
//    ui->tabWidget->setCurrentIndex(1); // 设置当前tabWidget活动标签页第2页
//    ui->tabWidget->setCurrentIndex(); // 获取当前tabWidget活动标签页


}

void MainWidget::on_tabWidget_currentChanged(int index)
{
    if(ui->tabWidget->currentIndex()==0)
    {
        ui->comboBox->setCurrentIndex(0);
        ui->label_6->setText("学 号：");
        ui->label_5->setVisible(true);
        ui->textEdit_5->setVisible(true);
        QStringList strs = {"        序号        ","        姓名        ", "        性别        ", "        年龄        ", "       学号        ", "      专业      "};
        ui->tableWidget->setHorizontalHeaderLabels(strs); //学生表头
        ui->tableWidget->setColumnHidden(5, false); // 显示第6列专业
    }
    else
    {
        ui->comboBox->setCurrentIndex(1);
        ui->label_6->setText("工 龄：");
        ui->label_5->setVisible(false);
        ui->textEdit_5->setVisible(false);
        QStringList strs = {"        序号        ","        姓名        ", "        性别        ", "        年龄        ", "       工龄        ", "      专业      "};
        ui->tableWidget->setHorizontalHeaderLabels(strs);//程序员表头
        ui->tableWidget->setColumnHidden(5, true); // 隐藏第6列专业
    }
//    ui->comboBox->setCurrentIndex(0); // 设置当前comboBox活动标签页第1页

    }

////右键允许用户将其保存成文件、删除
//void QWidget::contextMenuEvent(QContextMenuEvent *event)
//{
//    QMenu contextMenu(this);

//    QAction actionSave("保存为CSV", this);
//    connect(&actionSave, &QAction::triggered, this, &MainWidget::saveToCSV);
//    contextMenu.addAction(&actionSave);

//    QAction actionDelete("删除行", this);
//    connect(&actionDelete, &QAction::triggered, this, &MainWidget::deleteRows);
//    contextMenu.addAction(&actionDelete);

//    contextMenu.exec(event->globalPos());
//}

//void QWidget::saveToCSV()
//{
//    QString fileName = QFileDialog::getSaveFileName(this, tr("保存CSV"), ".", tr("CSV Files (*.csv)"));
//    if(fileName.isEmpty())
//        return;

//    QFile file(fileName);
//    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
//        return;

//    QTextStream out(&file);

//    // 遍历所有行和列，将选中的行保存到CSV文件
//    for(int row = 0; row < ui->tableWidget->rowCount(); row++)
//    {
//        QTableWidgetItem *checkBoxItem = ui->tableWidget->item(row, 0);
//        if(checkBoxItem->checkState() == Qt::Checked)
//        {
//            QStringList rowData;
//            // 注意：我们从第1列开始，因为第0列是复选框
//            for(int column = 1; column < ui->tableWidget->columnCount(); column++)
//            {
//                QTableWidgetItem *item = ui->tableWidget->item(row, column);
//                rowData << (item ? item->text() : "");
//            }
//            out << rowData.join(",") << "\n";
//        }
//    }

//    file.close();
//}
////为表格中每一行创建一个复选框，并在复选框选中的情况下，保存选中行的数据到CSV文件或者删除选中的行
//void QWidget::deleteRows()
//{
//    // 从下往上删除，避免改变正在处理的行索引
//    for(int row = ui->tableWidget->rowCount() - 1; row >= 0; row--)
//    {
//        QTableWidgetItem *checkBoxItem = ui->tableWidget->item(row, 0);
//        if(checkBoxItem->checkState() == Qt::Checked)
//        {
//            ui->tableWidget->removeRow(row);
//        }
//    }
//}


//左侧属性栏和右侧表格数据关联
//逻辑：通过槽函数 进行两次 数据同步 若数据不为空 则同步此数据到另一个内






MainWidget::~MainWidget()
{
    delete ui;
}

