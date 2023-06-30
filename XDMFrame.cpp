#include "XDMFrame.h"
#include "ui_XDMFrame.h"
#include <QCheckBox>

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTableWidgetItem>
#include <QMap>
#include  <QToolTip>
#include <QMessageBox>
#include <qDebug>
XDMFrame::XDMFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XDMFrame)
{
    ui->setupUi(this);  // 使用Qt Designer生成的代码加载UI布局

    QStringList header;
//    header<<"ID";   //添加QString字符串
    header<<"name";
    header<<"sex";
    header<<"age";
    header<<"xuehao";
    header<<"major";
    m_pStuTable = new XDMLogTable();
    m_pStuTable->setHeaderList(header);
    ui->tabWidget->addTab(m_pStuTable,"Student");

    //绑定表头和所在列
    enum StuColunm
    {
//        column_id = 0,
        column_name = 0,
        column_sex = 1,
        column_age = 2,
        column_xuehao = 3,
        column_major = 4
    };

//    table1HeaderList_stu.insert(column_id,"ID");
    table1HeaderList_stu.insert(column_name,"name");
    table1HeaderList_stu.insert(column_sex,"sex");
    table1HeaderList_stu.insert(column_age,"age");
    table1HeaderList_stu.insert(column_xuehao,"xuehao");
    table1HeaderList_stu.insert(column_major,"major");

    m_pStuTable->setHeaderList(table1HeaderList_stu.values());
    //获取列号  table1HeaderList.key("ID");

    header.clear();
//    header<<"ID";
    header<<"name";
    header<<"sex";
    header<<"age";
    header<<"gongling";

    m_pProgramTable = new XDMLogTable();
    m_pProgramTable->setHeaderList(header);
    ui->tabWidget->addTab(m_pProgramTable,"Programmer");
    //绑定表头和所在列
    enum ProColunm
    {
//        column_pid = 0,
        column_pname = 0,
        column_psex = 1,
        column_page = 2,
        column_pgongling = 3,
    };
//    table1HeaderList.clear(); // 清空
//    table1HeaderList_pro.insert(column_pid,"ID");
    table1HeaderList_pro.insert(column_pname,"name");
    table1HeaderList_pro.insert(column_psex,"sex");
    table1HeaderList_pro.insert(column_page,"age");
    table1HeaderList_pro.insert(column_pgongling,"gongling");

    m_pProgramTable->setHeaderList(table1HeaderList_pro.values());


    //初始化g_Table
    g_Table = m_pStuTable;

    //设置LineEdit属性及提示 age xuehao

    ui->lineEdit_age->setPlaceholderText(tr("请输入数字1-200"));
    ui->lineEdit_age->setValidator(new QRegExpValidator(QRegExp("^([1-9]|[1-9]\\d|1\\d{2}|200)$")));
//    ui->lineEdit_xuehao->setPlaceholderText(tr("请输入字母或数字"));
    ui->lineEdit_xuehao->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));


    //连接pushButton_Open按钮的clicked信号到槽函数slotSave
    connect(ui->pushButton_Open,SIGNAL(clicked(bool)),this,SLOT(slotSave()));
    connect(ui->pushButton_Add,SIGNAL(clicked(bool)),this,SLOT(slotAdd()));
    connect(ui->pushButton_Delete,SIGNAL(clicked(bool)),this,SLOT(slotDelet()));
    connect(ui->lineEdit_age,SIGNAL(textChanged(QString)),this,SLOT(slotlineEdit_Age(QString)));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slotComboBoxChange(int)));
    connect(ui->tabWidget,SIGNAL(tabBarClicked(int)),this,SLOT(slotTableWidgetChange(int)));

    //获取点击的单元格位置信息
    connect(g_Table,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(getItem(QModelIndex)));


   //Tab回车跳转LineEdit 设置下一个焦点  五个lineEdit使用 出现异常 （lineEdit的创建顺序问题 desingner添加）
//    setTabOrder(lineEdit_name, lineEdit_sex);
//    setTabOrder(lineEdit_sex, lineEdit_age);


//    connect(ui->lineEdit_name, &QLineEdit::editingFinished, this, &XDMFrame::slot)

//    connect(ui->tabWidget, &QTabWidget::)


//    QTableWidget *tab = new QTableWidget;
//    connect(tab, &QTableWidget::activated)


}

XDMFrame::~XDMFrame()
{

}

/**
 * @brief  当点击表格的某一行时，将当前行数据显示到左侧的属性栏中，用户可以在左侧属性栏修改后，同步在表格和链表中修改
 */



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

    g_Table->setRowCount(0);  // 先清空表格
    int lineCount = 0; // 计数器，用于跟踪行数
    while (!in.atEnd())
    {
        QString line = in.readLine();
        lineCount++;

        if (lineCount < 2)
            continue; // 跳过前两行表头

        QStringList fields = line.split(",");  // CSV文件的字段通常用逗号分隔

        int row = g_Table->rowCount();
        g_Table->insertRow(row);
        for (int column = 0; column < fields.size(); ++column)
        {
            QTableWidgetItem* item = new QTableWidgetItem(fields[column]);
            g_Table->setItem(row, column, item);
        }
    }

    file.close();

}



/**
 * @brief  添加信息到表格中
 */


void XDMFrame::slotAdd()
{      

    // 获取属性栏中的数据
    QString name = ui->lineEdit_name->text();
    QString sex = ui->comboBox_sex->currentText();
    QString age = ui->lineEdit_age->text();
    QString xuehao = ui->lineEdit_xuehao->text();
    QString major = ui->lineEdit_major->text();

    // 在表格中插入新行
    int row = g_Table->rowCount();
    g_Table->insertRow(row);

    // 将属性栏数据插入表格的相应列
    g_Table->setItem(row, table1HeaderList_stu.key("name"), new QTableWidgetItem(name));
    g_Table->setItem(row, table1HeaderList_stu.key("sex"), new QTableWidgetItem(sex));
    g_Table->setItem(row, table1HeaderList_stu.key("age"), new QTableWidgetItem(age));
    g_Table->setItem(row, table1HeaderList_stu.key("xuehao"), new QTableWidgetItem(xuehao));
    g_Table->setItem(row, table1HeaderList_stu.key("major"), new QTableWidgetItem(major));

    //添加后清空属性栏内容
    ui->lineEdit_name->clear();
    //    ui->lineEdit_sex->clear();
    QString defaultText = "男";
    ui->comboBox_sex->setCurrentText(defaultText);
    ui->lineEdit_age->clear();
    ui->lineEdit_xuehao->clear();
    ui->lineEdit_major->clear();


}


/**
 * @brief  删除信息
 */
void XDMFrame::slotDelet()
{

    // 创建一个提示框
    QMessageBox messageBox;
    messageBox.setIcon(QMessageBox::Question);
    messageBox.setWindowTitle("用户提示");
    messageBox.setText("请问是否删除？");
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    // 处理用户的选择
    int result = messageBox.exec();
    if (result == QMessageBox::Yes)
    {
        // 用户点击了"是"按钮，将选中数据删除
        QList<QTableWidgetItem*> selectedItems = g_Table->selectedItems();
        QSet<int> selectedRows;
        foreach(QTableWidgetItem* item, selectedItems) {
            selectedRows.insert(item->row());
        }
        // 将行号排序，并从最大的行号开始删除
        QList<int> sortedRows = QList<int>::fromSet(selectedRows);
        std::sort(sortedRows.begin(), sortedRows.end(), std::greater<int>());
        foreach(int row, sortedRows) {
            g_Table->removeRow(row);
        }
    }
    else
    {

    }


}

/**
 * @brief  年龄超过100岁提示
 */

void XDMFrame::slotlineEdit_Age(const QString &arg1)
{
    int age_int = ui->lineEdit_age->text().toInt(); // QString 转为 int
    if (age_int > 100) {
        // 创建一个提示框
        QMessageBox messageBox;
        messageBox.setIcon(QMessageBox::Question);
        messageBox.setWindowTitle("确认信息");
        messageBox.setText("年龄过大，请确认信息是否正确");
        messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        // 处理用户的选择
        int result = messageBox.exec();
        if (result == QMessageBox::Yes) {
            // 用户点击了"是"按钮，继续处理逻辑
            // ...
        } else {
            // 用户点击了"否"按钮，取消操作或进行其他处理
            ui->lineEdit_age->clear();
        }

    }
}


/**
 * @brief  combobox和tabwidget 关联 属性栏切换
 */


void XDMFrame::slotComboBoxChange(int index)
{
    if(ui->comboBox->currentIndex()==0)
    {
        //修改属性栏
        ui->tabWidget->setCurrentIndex(0);
        ui->xuehao->setText("学 号：");//重命名学号
        ui->lineEdit_major->setVisible(true);
        ui->major->setVisible(true);//重显示专业
        //更改表格
        g_Table= m_pStuTable;
    }
    else
    {
        ui->tabWidget->setCurrentIndex(1);
        ui->xuehao->setText("工 龄：");// 学号修改为工龄
        ui->lineEdit_major->setVisible(false);
        ui->major->setVisible(false);//隐藏属性栏专业
        ui->lineEdit_major->setVisible((false));//隐藏表格专业

        g_Table = m_pProgramTable;
     }

}

void XDMFrame::slotTableWidgetChange(int index)
{
    if(ui->tabWidget->currentIndex()==1)
    {
        //修改属性栏
        ui->comboBox->setCurrentIndex(0);
        ui->xuehao->setText("学 号：");//重命名学号
        ui->lineEdit_major->setVisible(true);
        ui->major->setVisible(true);//重显示专业
        //更改表格
        g_Table= m_pStuTable;
    }
    else
    {
        ui->comboBox->setCurrentIndex(1);
        ui->xuehao->setText("工 龄：");// 学号修改为工龄
        ui->lineEdit_major->setVisible(false);
        ui->major->setVisible(false);//隐藏属性栏专业
        ui->lineEdit_major->setVisible((false));//隐藏表格专业
        g_Table = m_pProgramTable;
     }
}


/**
 * @brief  选中某一行 数据显示到左侧的属性栏中
 */


void XDMFrame::getItem(const QModelIndex &index)
{
//    //设备编号
//        QString num = ui->tableWidget->model()->index(index.row(),1).data().toString(); //使用一个字符串接收
//        ui->m_num_lineEdit->setText(num); //把这个字符串显示在相应的lineEdit控件上
//        //IP地址
//        QString ip = ui->tableWidget->model()->index(index.row(),3).data().toString();
//        ui->m_ip_lineEdit->setText(ip);
//        //其他把列数修改为对应列，序号皆为由0开始
//    ui->xuehao->setText("表格点击测试成功：");
}



