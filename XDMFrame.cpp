#include "XDMFrame.h"
#include "ui_XDMFrame.h"
#include <QCheckBox>

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTableWidgetItem>
#include <QMap>
#include <QToolTip>
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
    g_Table->getTableName("s");
    //设置LineEdit属性及提示 age xuehao


    ui->lineEdit_age->setPlaceholderText(tr("请输入数字1-200"));
    ui->lineEdit_age->setValidator(new QRegExpValidator(QRegExp("^([1-9]|[1-9]\\d|1\\d{2}|200)$")));
//    ui->lineEdit_xuehao->setPlaceholderText(tr("请输入字母或数字"));
    ui->lineEdit_xuehao->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));


    //连接pushButton_Open按钮的clicked信号到槽函数slotSave
    connect(ui->pushButton_Open,SIGNAL(clicked(bool)),this,SLOT(slotSave()));
    connect(ui->pushButton_Add,SIGNAL(clicked(bool)),this,SLOT(slotAdd()));
    connect(ui->pushButton_Delete,SIGNAL(clicked(bool)),this,SLOT(slotDelete()));

    connect(ui->lineEdit_age,SIGNAL(textChanged(QString)),this,SLOT(slotlineEdit_Age(QString)));
    //类型和tab切换
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slotComboBoxChange(int)));
    connect(ui->tabWidget,SIGNAL(tabBarClicked(int)),this,SLOT(slotTableWidgetChange(int)));

    //分页按钮
    connect(ui->pushButton_HomePage,SIGNAL(clicked(bool)),this,SLOT(slotHomePage()));
    connect(ui->pushButton_PageUp,SIGNAL(clicked(bool)),this,SLOT(slotPageUp()));
    connect(ui->pushButton_PageDown,SIGNAL(clicked(bool)),this,SLOT(slotPageDown()));
    connect(ui->pushButton_LastPage,SIGNAL(clicked(bool)),this,SLOT(slotLastPage()));
    connect(ui->pushButton_Redirect,SIGNAL(clicked(bool)),this,SLOT(slotRedirect()));



    //   Tab回车跳转LineEdit 设置下一个焦点  五个lineEdit使用 出现异常 （lineEdit的创建顺序问题 desingner添加）
//    setTabOrder(lineEdit_name, lineEdit_sex);
//    setTabOrder(lineEdit_sex, lineEdit_age);


//    connect(ui->lineEdit_name, &QLineEdit::editingFinished, this, &XDMFrame::slot)

//    connect(ui->tabWidget, &QTabWidget::)


//    QTableWidget *tab = new QTableWidget;
//    connect(tab, &QTableWidget::activated)

    connect(g_Table, &XDMLogTable::sendToXDMF, this, &XDMFrame::slotlineEdit); // 同步属性栏lineEdit内容 接收xdmlogtable中的emit 发出的信号

    this->updateCur();

}

XDMFrame::~XDMFrame()
{

}

void XDMFrame::lineEditClear()
{
    ui->lineEdit_age->clear();
    ui->lineEdit_name->clear();
    ui->lineEdit_xuehao->clear();
    ui->lineEdit_major->clear();
    //    QString defaultText = "男";
    //    ui->comboBox_sex->setCurrentText(defaultText);
    ui->comboBox_sex->setCurrentIndex(0);
}

void XDMFrame::updateCur()
{
    if (this->g_Table->tableName == "s"){
        qDebug() << this->currentPage_1;
        ui->curpage->setText("第" + QString::number(this->currentPage_1) + "页");
    }
    else{
        qDebug() << this->currentPage_2;
        ui->curpage->setText("第" + QString::number(this->currentPage_2) + "页");
    }
}



/**
 * @brief 保存界面填充的录入信息
 */


void XDMFrame::slotSave()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open CSV"), ".", tr("CSV Files (*.csv)"));
    if(fileName.isEmpty())
    {
        return;
    }
    else
    {
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

            if (lineCount < 2){
                continue; // 跳过前两行表头
            }
            QStringList fields = line.split(",");  // CSV文件的字段通常用逗号分隔
            if (g_Table->tableName == "s"){
                Student s(fields[0], fields[1], fields[2].toInt());
                s.setMajor(fields[4]);
                s.setXuehao(fields[3]);
                s_list.append(s);
            }
            else{
                Programmer p(fields[0], fields[1], fields[2].toInt());
                p.setGongling(fields[3]);
                p_list.append(p);
            }
            int row = g_Table->rowCount();
            if (row < 10){
                g_Table->insertRow(row);
                for (int column = 0; column < fields.size(); ++column)
                {
                    QTableWidgetItem* item = new QTableWidgetItem(fields[column]);
                    g_Table->setItem(row, column, item);
                }
            }
        }
        if (g_Table->tableName == "s"){
            this->allPage_1 = s_list.length() / 10 + 1;
        }
        else{
            this->allPage_2 = p_list.length() / 10 + 1;
        }
        file.close();

    }
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

//    Student s();


    // 在表格中插入新行
    int row = g_Table->rowCount();
    g_Table->insertRow(row);
    if (row == 10){
        g_Table->clearContents();
        g_Table->setRowCount(0);
        this->currentPage_1++;
        row = 0;
        g_Table->insertRow(row);
    }
    if (row < 10){
        // 将属性栏数据插入表格的相应列
        g_Table->setItem(row, table1HeaderList_stu.key("name"), new QTableWidgetItem(name));
        g_Table->setItem(row, table1HeaderList_stu.key("sex"), new QTableWidgetItem(sex));
        g_Table->setItem(row, table1HeaderList_stu.key("age"), new QTableWidgetItem(age));
        g_Table->setItem(row, table1HeaderList_stu.key("xuehao"), new QTableWidgetItem(xuehao));
        g_Table->setItem(row, table1HeaderList_stu.key("major"), new QTableWidgetItem(major));
    }

    //添加后清空属性栏内容
    ui->lineEdit_name->clear();
    //    ui->lineEdit_sex->clear();
    QString defaultText = "男";
    ui->comboBox_sex->setCurrentText(defaultText);
    ui->lineEdit_age->clear();
    ui->lineEdit_xuehao->clear();
    ui->lineEdit_major->clear();

    this->updateCur();
}


/**
 * @brief  删除信息
 */
void XDMFrame::slotDelete()
{

    // 创建一个提示框
    QMessageBox::StandardButton result = QMessageBox::question(this, "用户提示", "请问是否删除？", QMessageBox::Yes | QMessageBox::No);

//    QMessageBox messageBox;
//    messageBox.setIcon(QMessageBox::Question);
//    messageBox.setWindowTitle("用户提示");
//    messageBox.setText("请问是否删除？");
//    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    // 处理用户的选择
//    int result = messageBox.exec();
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
        QMessageBox::StandardButton result = QMessageBox::question(this, "确认信息", "年龄过大，请确认信息是否正确？", QMessageBox::Yes | QMessageBox::No);

        // 处理用户的选择
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
    disconnect(g_Table, &XDMLogTable::sendToXDMF, this, &XDMFrame::slotlineEdit);
    if(ui->comboBox->currentIndex()==0)
    {
        //修改属性栏
        ui->tabWidget->setCurrentIndex(0);
        ui->xuehao->setText("学 号：");//重命名学号
        ui->lineEdit_major->setVisible(true);
        ui->major->setVisible(true);//重显示专业
        //更改表格
        g_Table= m_pStuTable;
        g_Table->getTableName("s");
    }
    else
    {
        ui->tabWidget->setCurrentIndex(1);
        ui->xuehao->setText("工 龄：");// 学号修改为工龄
        ui->lineEdit_major->setVisible(false);
        ui->major->setVisible(false);//隐藏属性栏专业
        ui->lineEdit_major->setVisible((false));//隐藏表格专业

        g_Table = m_pProgramTable;
        g_Table->getTableName("p");
     }
    connect(g_Table, &XDMLogTable::sendToXDMF, this, &XDMFrame::slotlineEdit);
    this->lineEditClear();
}

void XDMFrame::slotTableWidgetChange(int index)
{
    disconnect(g_Table, &XDMLogTable::sendToXDMF, this, &XDMFrame::slotlineEdit);
    if(ui->tabWidget->currentIndex()==1)
    {
        //修改属性栏
        ui->comboBox->setCurrentIndex(0);
        ui->xuehao->setText("学 号：");//重命名学号
        ui->lineEdit_major->setVisible(true);
        ui->major->setVisible(true);//重显示专业
        //更改表格
        g_Table= m_pStuTable;
        g_Table->getTableName("s");
    }
    else
    {
        ui->comboBox->setCurrentIndex(1);
        ui->xuehao->setText("工 龄：");// 学号修改为工龄
        ui->lineEdit_major->setVisible(false);
        ui->major->setVisible(false);//隐藏属性栏专业
        ui->lineEdit_major->setVisible((false));//隐藏表格专业
        g_Table = m_pProgramTable;
        g_Table->getTableName("p");
     }
    //table发送信息到Lineedit
    connect(g_Table, &XDMLogTable::sendToXDMF, this, &XDMFrame::slotlineEdit);
    ui->lineEdit_age->clear();
    ui->lineEdit_name->clear();
    ui->lineEdit_xuehao->clear();
    ui->lineEdit_major->clear();
//    QString defaultText = "男";
//    ui->comboBox_sex->setCurrentText(defaultText);
    ui->comboBox_sex->setCurrentIndex(0);
}


/**
 * @brief  分页按钮
 *
 */

void XDMFrame::slotHomePage()
{
    g_Table->clearContents();
    int row = 0;
    int all;
//    this->currentPage_1 = 1;
//    this->currentPage_2 = 1;
    if (ui->tabWidget->currentIndex() == 0)
    {
        if (s_list.length() > 9){
            all = 9;
        }
        else{
            all = s_list.length();
        }
        for (int i = 0; i <= all; i++){
            QTableWidgetItem* item1 = new QTableWidgetItem(s_list[i].name);
            g_Table->setItem(row, 0, item1);
            QTableWidgetItem* item2 = new QTableWidgetItem(s_list[i].sex);
            g_Table->setItem(row, 1, item2);
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(s_list[i].age));
            g_Table->setItem(row, 2, item3);
            QTableWidgetItem* item4 = new QTableWidgetItem(s_list[i].getXuehao());
            g_Table->setItem(row, 3, item4);
            QTableWidgetItem* item5 = new QTableWidgetItem(s_list[i].getMajor());
            g_Table->setItem(row, 4, item5);
            row++;
        }
            this->currentPage_1 = 1;
    }
    else
    {
        if (p_list.length() > 9){
            all = 9;
        }
        else{
            all = p_list.length();
        }
        for (int i = 0; i <= all; i++){
            QTableWidgetItem* item1 = new QTableWidgetItem(p_list[i].name);
            g_Table->setItem(row, 0, item1);
            QTableWidgetItem* item2 = new QTableWidgetItem(p_list[i].sex);
            g_Table->setItem(row, 1, item2);
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(p_list[i].age));
            g_Table->setItem(row, 2, item3);
            QTableWidgetItem* item4 = new QTableWidgetItem(p_list[i].getGongling());
            g_Table->setItem(row, 3, item4);
            row++;
        }
        this->currentPage_2 = 1;
    }
    this->updateCur();

}

void XDMFrame::slotPageUp()
{
    g_Table->clearContents();
    int row = 0;
    if (ui->tabWidget->currentIndex() == 1)
    {
        this->currentPage_2--;
        int frist = 0, end = 9;
        int currentPage = this->currentPage_2;
        frist = frist + 10 * (currentPage - 1);
        end = end  + 10 * (currentPage - 1);
        if (end > p_list.length()){
            end = p_list.length() - 1;
        }
        for (int i = frist; i <= end; i++){
            QTableWidgetItem* item1 = new QTableWidgetItem(p_list[i].name);
            g_Table->setItem(row, 0, item1);
            QTableWidgetItem* item2 = new QTableWidgetItem(p_list[i].sex);
            g_Table->setItem(row, 1, item2);
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(p_list[i].age));
            g_Table->setItem(row, 2, item3);
            QTableWidgetItem* item4 = new QTableWidgetItem(p_list[i].getGongling());
            g_Table->setItem(row, 3, item4);
            row++;
        }
    }
    else
    {
        this->currentPage_1--;
        int frist = 0, end = 9;
        int currentPage = this->currentPage_1;
        frist = frist + 10 * (currentPage - 1);
        end = end  + 10 * (currentPage - 1);
        if (end > s_list.length()){
            end = s_list.length() - 1;
        }
        for (int i = frist; i <= end; i++){
            QTableWidgetItem* item1 = new QTableWidgetItem(s_list[i].name);
            g_Table->setItem(row, 0, item1);
            QTableWidgetItem* item2 = new QTableWidgetItem(s_list[i].sex);
            g_Table->setItem(row, 1, item2);
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(s_list[i].age));
            g_Table->setItem(row, 2, item3);
            QTableWidgetItem* item4 = new QTableWidgetItem(s_list[i].getXuehao());
            g_Table->setItem(row, 3, item4);
            QTableWidgetItem* item5 = new QTableWidgetItem(s_list[i].getMajor());
            g_Table->setItem(row, 4, item5);
            row++;
        }
    }
    this->updateCur();
}

void XDMFrame::slotPageDown()
{
    g_Table->clearContents();
    int row = 0;
    if (ui->tabWidget->currentIndex() == 1)
    {
        this->currentPage_2++;
        int frist = 0, end = 9;
        int currentPage = this->currentPage_2;
        frist = frist + 10 * (currentPage - 1);
        end = end  + 10 * (currentPage - 1);
        if (end > p_list.length()){
            end = p_list.length() - 1;
        }
        for (int i = frist; i <= end; i++){
            QTableWidgetItem* item1 = new QTableWidgetItem(p_list[i].name);
            g_Table->setItem(row, 0, item1);
            QTableWidgetItem* item2 = new QTableWidgetItem(p_list[i].sex);
            g_Table->setItem(row, 1, item2);
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(p_list[i].age));
            g_Table->setItem(row, 2, item3);
            QTableWidgetItem* item4 = new QTableWidgetItem(p_list[i].getGongling());
            g_Table->setItem(row, 3, item4);
            row++;
        }
    }
    else
    {
        this->currentPage_1++;
        int frist = 0, end = 9;
        int currentPage = this->currentPage_1;
        frist = frist + 10 * (currentPage - 1);
        end = end  + 10 * (currentPage - 1);
        if (end > s_list.length()){
            end = s_list.length() - 1;
        }
        for (int i = frist; i <= end; i++){
            QTableWidgetItem* item1 = new QTableWidgetItem(s_list[i].name);
            g_Table->setItem(row, 0, item1);
            QTableWidgetItem* item2 = new QTableWidgetItem(s_list[i].sex);
            g_Table->setItem(row, 1, item2);
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(s_list[i].age));
            g_Table->setItem(row, 2, item3);
            QTableWidgetItem* item4 = new QTableWidgetItem(s_list[i].getXuehao());
            g_Table->setItem(row, 3, item4);
            QTableWidgetItem* item5 = new QTableWidgetItem(s_list[i].getMajor());
            g_Table->setItem(row, 4, item5);
            row++;
        }
    }
    this->updateCur();
}

void XDMFrame::slotLastPage()
{
    g_Table->clearContents();
    int row = 0;
    if (ui->tabWidget->currentIndex() == 1)
    {
        this->currentPage_2 = this->allPage_2;
        int frist = 0, end = 9;
        int currentPage = this->currentPage_2;
        frist = frist + 10 * (currentPage - 1);
        end = end  + 10 * (currentPage - 1);
        if (end > p_list.length()){
            end = p_list.length() - 1;
        }
        for (int i = frist; i <= end; i++){
            QTableWidgetItem* item1 = new QTableWidgetItem(p_list[i].name);
            g_Table->setItem(row, 0, item1);
            QTableWidgetItem* item2 = new QTableWidgetItem(p_list[i].sex);
            g_Table->setItem(row, 1, item2);
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(p_list[i].age));
            g_Table->setItem(row, 2, item3);
            QTableWidgetItem* item4 = new QTableWidgetItem(p_list[i].getGongling());
            g_Table->setItem(row, 3, item4);
            row++;
        }
    }
    else
    {
        this->currentPage_1= this->allPage_1;
        int frist = 0, end = 9;
        int currentPage = this->currentPage_1;
        frist = frist + 10 * (currentPage - 1);
        end = end  + 10 * (currentPage - 1);
        if (end > s_list.length()){
            end = s_list.length() - 1;
        }
        for (int i = frist; i <= end; i++){
            QTableWidgetItem* item1 = new QTableWidgetItem(s_list[i].name);
            g_Table->setItem(row, 0, item1);
            QTableWidgetItem* item2 = new QTableWidgetItem(s_list[i].sex);
            g_Table->setItem(row, 1, item2);
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(s_list[i].age));
            g_Table->setItem(row, 2, item3);
            QTableWidgetItem* item4 = new QTableWidgetItem(s_list[i].getXuehao());
            g_Table->setItem(row, 3, item4);
            QTableWidgetItem* item5 = new QTableWidgetItem(s_list[i].getMajor());
            g_Table->setItem(row, 4, item5);
            row++;
        }
    }
    this->updateCur();
}

void XDMFrame::slotRedirect()
{

}

void XDMFrame::slotlineEdit(QStringList sl)
{
//    qDebug() << "11";
    ui->lineEdit_name->setText(sl[0]);
    ui->comboBox_sex->setCurrentText(sl[1]);
    ui->lineEdit_age->setText(sl[2]);
    if (g_Table->tableName == "s"){
        ui->lineEdit_xuehao->setText(sl[3]);
        ui->lineEdit_major->setText(sl[4]);
    }
    else{
        ui->lineEdit_xuehao->setText(sl[3]);
    }
}
