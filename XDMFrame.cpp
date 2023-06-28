#include "XDMFrame.h"
#include "ui_XDMFrame.h"
#include <QCheckBox>

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTableWidgetItem>

//#include <QTableWidget>
//#include <QTableWidgetItem>
//#include <QApplication>

//#include <QMenu>
//#include <QAction>
//#include <QFileDialog>
//#include <QFile>
//#include <QTextStream>

//#include <QWidget>
//#include <QContextMenuEvent>


XDMFrame::XDMFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XDMFrame)
{
    ui->setupUi(this);  // 使用Qt Designer生成的代码加载UI布局
//    XDMLogTable  * m_pStuTable =new XDMLogTable();
    QStringList header;
    header<<"ID";   //添加QString字符串
    header<<"name";
    header<<"sex";
    header<<"age";
    header<<"xuehao";
    header<<"major";
    m_pStuTable = new XDMLogTable();
    m_pStuTable->setHeaderList(header);
    ui->tabWidget->addTab(m_pStuTable,"Student");

    header.clear();
    header<<"ID";
    header<<"name";
    header<<"sex";
    header<<"age";
    header<<"gongling";
    m_pProgramTable = new XDMLogTable();
    m_pProgramTable->setHeaderList(header);
    ui->tabWidget->addTab(m_pProgramTable,"Programmer");

    //连接pushButton_Open按钮的clicked信号到槽函数slotSave
    connect(ui->pushButton_Open,SIGNAL(clicked(bool)),this,SLOT(slotSave()));
    connect(ui->pushButton_Add,SIGNAL(clicked(bool)),this,SLOT(slotAdd()));
    connect(ui->pushButton_Delete,SIGNAL(clicked(bool)),this,SLOT(SlotDelete));

    //Tab回车跳转LineEdit 设置下一个焦点  五个lineEdit使用 出现异常

    setTabOrder(lineEdit_name, lineEdit_sex);
    setTabOrder(lineEdit_sex, lineEdit_age);

}

XDMFrame::~XDMFrame()
{

}

/**
 * @brief 保存界面填充的录入信息
 */


void XDMFrame::slotSave()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open CSV"), ".", tr("CSV Files (*.csv)"));
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    m_pStuTable->setRowCount(0);  // 先清空表格
    int lineCount = 0; // 计数器，用于跟踪行数
    while (!in.atEnd())
    {
        QString line = in.readLine();
        lineCount++;

        if (lineCount < 2)
            continue; // 跳过前两行表头

        QStringList fields = line.split(",");  // CSV文件的字段通常用逗号分隔

        int row = m_pStuTable->rowCount();
        m_pStuTable->insertRow(row);
        for (int column = 0; column < fields.size(); ++column)
        {
            QTableWidgetItem* item = new QTableWidgetItem(fields[column]);
            m_pStuTable->setItem(row, column, item);
        }
    }

    file.close();

}

/**
 * @brief  判断当前表格类型
 */



/**
 * @brief  添加信息到表格中
 */


void XDMFrame::slotAdd()
{


    static int rowCounter = 0; // 记录添加的行数
    // 获取当前表格的行数
    int row = m_pStuTable->rowCount();
    // 插入新行
    m_pStuTable->insertRow(rowCounter);
    // 设置序号
    QTableWidgetItem *indexItem = new QTableWidgetItem(QString::number(rowCounter + 1));
    m_pStuTable->setItem(rowCounter, 0, indexItem);
    // 添加列表格

    // 获取 QLineEdit 的内容
    QString text_name = ui->lineEdit_name->text();
    QString text_sex = ui->lineEdit_sex->text();
    QString text_age = ui->lineEdit_age->text();
    QString text_xuehao = ui->lineEdit_xuehao->text();
    QString text_major = ui->lineEdit_major->text();


    // 设置表格单元格内容
    QTableWidgetItem *nameC = new QTableWidgetItem(text_name);
    QTableWidgetItem *sexC = new QTableWidgetItem(text_sex);
    QTableWidgetItem *ageC = new QTableWidgetItem(text_age);
    QTableWidgetItem *xuehaoC = new QTableWidgetItem(text_xuehao);
    QTableWidgetItem *majorC = new QTableWidgetItem(text_major);

    //添加内容至表格
//    m_pStuTable->setItem(row, 1, nameC); // 第一列
    m_pStuTable->setItem(row, 2, sexC);
    m_pStuTable->setItem(row, 3, ageC);
    m_pStuTable->setItem(row, 4, xuehaoC);
    m_pStuTable->setItem(row, 5, majorC);
    m_pStuTable->setItem(rowCounter, 1, nameC);
    rowCounter++;

    //添加后清空属性栏内容
    ui->lineEdit_name->clear();
    ui->lineEdit_sex->clear();
    ui->lineEdit_age->clear();
    ui->lineEdit_xuehao->clear();
    ui->lineEdit_major->clear();

}


/**
 * @brief  删除信息
 */
void XDMFrame::slotDelet()
{

}
