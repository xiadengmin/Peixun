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

#include <QSqlQuery>
#include <QSqlError>

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
//    m_pStuTable->currentRow();
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
//    connect(ui->tabWidget,SIGNAL(tabBarClicked(int)),this,SLOT(slotTableWidgetChange(int)));

    //分页按钮
    connect(ui->pushButton_HomePage,SIGNAL(clicked(bool)),this,SLOT(slotHomePage()));
    connect(ui->pushButton_PageUp,SIGNAL(clicked(bool)),this,SLOT(slotPageUp()));
    connect(ui->pushButton_PageDown,SIGNAL(clicked(bool)),this,SLOT(slotPageDown()));
    connect(ui->pushButton_LastPage,SIGNAL(clicked(bool)),this,SLOT(slotLastPage()));
    connect(ui->pushButton_Redirect,SIGNAL(clicked(bool)),this,SLOT(slotRedirect(bool)));



    //   Tab回车跳转LineEdit 设置下一个焦点  五个lineEdit使用 出现异常 （lineEdit的创建顺序问题 desingner添加）
//    setTabOrder(lineEdit_name, lineEdit_sex);
//    setTabOrder(lineEdit_sex, lineEdit_age);


//    connect(ui->lineEdit_name, &QLineEdit::editingFinished, this, &XDMFrame::slot)

//    connect(ui->tabWidget, &QTabWidget::)


//    QTableWidget *tab = new QTableWidget;
//    connect(tab, &QTableWidget::activated)

    connect(g_Table, &XDMLogTable::sendToXDMF, this, &XDMFrame::slotlineEdit); // 同步属性栏lineEdit内容 接收xdmlogtable中的emit 发出的信号

    this->updateCur();
    this->update();

    QSqlQuery query;
    query.exec("select * from student");
    while (query.next()){
        int row = m_pStuTable->rowCount();
        if (row < 10){
            m_pStuTable->insertRow(row);
            for (int i = 1; i < 6; i++){
                QTableWidgetItem* item = new QTableWidgetItem(query.value(i).toString());
                m_pStuTable->setItem(row, i - 1, item);
            }
        }
    }

    query.exec("select * from programmer");
    while (query.next()){
        int row = m_pProgramTable->rowCount();
        if (row < 10){
            m_pProgramTable->insertRow(row);
            for (int i = 1; i < 6; i++){
                QTableWidgetItem* item = new QTableWidgetItem(query.value(i).toString());
                m_pProgramTable->setItem(row, i - 1, item);
            }
        }
    }

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
<<<<<<< HEAD
//        qDebug() << this->currentPage_1;
=======
>>>>>>> 5a22ea0 (mysql_2)
        ui->curpage->setText("第" + QString::number(this->currentPage_1) + "页");
    }
    else{
//        qDebug() << this->currentPage_2;
        ui->curpage->setText("第" + QString::number(this->currentPage_2) + "页");
    }
}

void XDMFrame::update()
{
    s_list.clear();
    QSqlQuery query;
    query.exec("select * from student");
    while (query.next()){
        Student s(query.value(1).toString(), query.value(2).toString(), query.value(3).toInt());
        s.setXuehao(query.value(4).toString());
        s.setMajor(query.value(5).toString());
        s_list.append(s);
    }
    this->allPage_1 = qCeil(double(s_list.length()) / 10.0);

    p_list.clear();
    query.exec("select * from programmer");
    while (query.next()){
        Programmer p(query.value(1).toString(), query.value(2).toString(), query.value(3).toInt());
        p.setGongling(query.value(4).toString());
        p_list.append(p);
    }
    this->allPage_2 = qCeil(double(p_list.length()) / 10.0);
}


void XDMFrame::refreshPage()
{
    g_Table->clearContents();
    g_Table->setRowCount(0);
    int frist = 0, end = 9;
    if (g_Table->tableName == "p"){
        int currentPage = this->currentPage_2;
        frist = frist + 10 * (currentPage - 1);
        end = end  + 10 * (currentPage - 1);
        if (end > p_list.length()){
            end = p_list.length() - 1;
        }
        for (int i = frist; i <= end; i++){
            int row = g_Table->rowCount();
            g_Table->insertRow(row);
            QTableWidgetItem* item1 = new QTableWidgetItem(p_list[i].name);
            g_Table->setItem(row, 0, item1);
            QTableWidgetItem* item2 = new QTableWidgetItem(p_list[i].sex);
            g_Table->setItem(row, 1, item2);
            QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(p_list[i].age));
            g_Table->setItem(row, 2, item3);
            QTableWidgetItem* item4 = new QTableWidgetItem(p_list[i].getGongling());
            g_Table->setItem(row, 3, item4);
        }
    }
    else{
        int currentPage = this->currentPage_1;
        frist = frist + 10 * (currentPage - 1);
        end = end  + 10 * (currentPage - 1);
        if (end > s_list.length()){
            end = s_list.length() - 1;
        }
        for (int i = frist; i <= end; i++){
            int row = g_Table->rowCount();
            g_Table->insertRow(row);
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
        }
    }
}



/**
 * @brief 保存界面填充的录入信息
 */


void XDMFrame:: slotSave()
{
    s_list.clear();
    p_list.clear();
<<<<<<< HEAD
=======
    //清空数据库

>>>>>>> 5a22ea0 (mysql_2)
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open CSV"), ".", tr("CSV Files (*.csv)"));
    if(fileName.isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("已取消csv文件打开"));
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
            int sex;
            if (fields[1] == "男"){
                sex = 1;
            }
            else{
                sex = 0;
            }
            if (g_Table->tableName == "s"){
                Student s(fields[0], fields[1], fields[2].toInt());
                s.setMajor(fields[4]);
                s.setXuehao(fields[3]);
                s_list.append(s);

                // 将学生数据插入到数据库表中
                QSqlQuery query;
                query.prepare("INSERT INTO student (name, sex, age, xuehao, major) "
                              "VALUES (:name, :sex, :age, :xuehao, :major)");
                query.bindValue(":name", fields[0]);
<<<<<<< HEAD
                query.bindValue(":sex", fields[1]);
=======
                query.bindValue(":sex", sex);
>>>>>>> 5a22ea0 (mysql_2)
                query.bindValue(":age", fields[2]);
                query.bindValue(":xuehao", fields[3]);
                query.bindValue(":major", fields[4]);
                query.exec();

            }
            else{
                Programmer p(fields[0], fields[1], fields[2].toInt());
                p.setGongling(fields[3]);
                p_list.append(p);

                // 将程序员数据插入到数据库表中
                QSqlQuery query;
                query.prepare("INSERT INTO programmer (name, sex, age, gongling) "
                              "VALUES (:name, :sex, :age, :gongling)");
                query.bindValue(":name", fields[0]);
<<<<<<< HEAD
                query.bindValue(":sex", fields[1]);
=======
                query.bindValue(":sex", sex);
>>>>>>> 5a22ea0 (mysql_2)
                query.bindValue(":age", fields[2]);
                query.bindValue(":gongling", fields[3]);
                query.exec();

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
<<<<<<< HEAD

    if(g_Table ==m_pStuTable)
    {
        // 获取属性栏中的数据
        QString name = ui->lineEdit_name->text();
        QString sex = ui->comboBox_sex->currentText();
        int age = ui->lineEdit_age->text().toInt();
        //    QString age = ui->lineEdit_age->text();
        QString xuehao = ui->lineEdit_xuehao->text();
        QString major = ui->lineEdit_major->text();

        Student s(name,sex,age);
        s.setXuehao(xuehao);
        s.setMajor(major);
        s_list.append(s);

        // 将学生数据插入到数据库表中
        QSqlQuery query;
        query.prepare("INSERT INTO student (name, sex, age, xuehao, major) "
                      "VALUES (:name, :sex, :age, :xuehao, :major)");
        query.bindValue(":name", name);
        query.bindValue(":sex", sex);
        query.bindValue(":age", age);
        query.bindValue(":xuehao", xuehao);
        query.bindValue(":major", major);
        query.exec();

        if (s_list.size() <= 10)
        {
            int row = g_Table->rowCount();
            g_Table->insertRow(row);

            // 将属性栏数据插入表格的相应列
            g_Table->setItem(row, table1HeaderList_stu.key("name"), new QTableWidgetItem(name));
            g_Table->setItem(row, table1HeaderList_stu.key("sex"), new QTableWidgetItem(sex));
            g_Table->setItem(row, table1HeaderList_stu.key("age"), new QTableWidgetItem(QString::number(age)));
            g_Table->setItem(row, table1HeaderList_stu.key("xuehao"), new QTableWidgetItem(xuehao));
            g_Table->setItem(row, table1HeaderList_stu.key("major"), new QTableWidgetItem(major));
        }
        if (s_list.size() > 10 && (s_list.size() - 1) % 10 == 1)
        {
            this->slotPageDown();
            //显示下一页
        }

=======
    if (ui->lineEdit_xuehao->text() == ""){
        QMessageBox::critical(this, "提示", "学号不能为空");
        return;
>>>>>>> 5a22ea0 (mysql_2)
    }
    else
    {
        // 获取属性栏中的数据
        QString name = ui->lineEdit_name->text();
        QString sex = ui->comboBox_sex->currentText();
        int age = ui->lineEdit_age->text().toInt();
        //    QString age = ui->lineEdit_age->text();
        QString gongling = ui->lineEdit_xuehao->text();
//        qDebug()<<ui->lineEdit_xuehao->text();

<<<<<<< HEAD
        Programmer p(name,sex,age);
=======
    if(g_Table == m_pStuTable)
    {
        QSqlQuery query;
        query.exec("select * from student;");
        while (query.next())
        {
            if (query.value(4).toString() == ui->lineEdit_xuehao->text()){
                QMessageBox::critical(this, "提示", "学号已存在，请重新输入");
                return;
            }
        }
        // 获取属性栏中的数据
        QString name = ui->lineEdit_name->text();
        int sex;
        if (ui->comboBox_sex->currentText() == "男"){
            sex = 1;
        }
        else{
            sex = 0;
        }
        int age = ui->lineEdit_age->text().toInt();
        //    QString age = ui->lineEdit_age->text();
        QString xuehao = ui->lineEdit_xuehao->text();
        QString major = ui->lineEdit_major->text();

        Student s(name,ui->comboBox_sex->currentText(),age);
        s.setXuehao(xuehao);
        s.setMajor(major);
        s_list.append(s);

        // 将学生数据插入到数据库表中
        query.prepare("INSERT INTO student (name, sex, age, xuehao, major) "
                      "VALUES (:name, :sex, :age, :xuehao, :major)");
        query.bindValue(":name", name);
        query.bindValue(":sex", sex);
        query.bindValue(":age", age);
        query.bindValue(":xuehao", xuehao);
        query.bindValue(":major", major);
        query.exec();

        if (s_list.size() <= 10)
        {
            int row = g_Table->rowCount();
            g_Table->insertRow(row);

            // 将属性栏数据插入表格的相应列
            g_Table->setItem(row, table1HeaderList_stu.key("name"), new QTableWidgetItem(name));
            g_Table->setItem(row, table1HeaderList_stu.key("sex"), new QTableWidgetItem(sex));
            g_Table->setItem(row, table1HeaderList_stu.key("age"), new QTableWidgetItem(QString::number(age)));
            g_Table->setItem(row, table1HeaderList_stu.key("xuehao"), new QTableWidgetItem(xuehao));
            g_Table->setItem(row, table1HeaderList_stu.key("major"), new QTableWidgetItem(major));
        }
        if (s_list.size() > 10 && s_list.size() % 10 == 1)
        {
            this->slotPageDown();
            //显示下一页
        }

    }
    else
    {
        // 获取属性栏中的数据
        QString name = ui->lineEdit_name->text();
        QString sex = ui->comboBox_sex->currentText();
        int age = ui->lineEdit_age->text().toInt();
        //    QString age = ui->lineEdit_age->text();
        QString gongling = ui->lineEdit_xuehao->text();
//        qDebug()<<ui->lineEdit_xuehao->text();

        Programmer p(name,ui->comboBox_sex->currentText(),age);
>>>>>>> 5a22ea0 (mysql_2)
        p.setGongling(gongling);
        p_list.append(p);

        // 将程序员数据插入到数据库表中
        QSqlQuery query;
        query.prepare("INSERT INTO programmer (name, sex, age, gongling) "
                      "VALUES (:name, :sex, :age, :gongling)");
        query.bindValue(":name", name);
        query.bindValue(":sex", sex);
        query.bindValue(":age", age);
        query.bindValue(":gongling", gongling);
        query.exec();

        if (p_list.size() <= 10)
        {
            int row = g_Table->rowCount();
            g_Table->insertRow(row);

            // 将属性栏数据插入表格的相应列
            g_Table->setItem(row, table1HeaderList_stu.key("name"), new QTableWidgetItem(name));
            g_Table->setItem(row, table1HeaderList_stu.key("sex"), new QTableWidgetItem(sex));
            g_Table->setItem(row, table1HeaderList_stu.key("age"), new QTableWidgetItem(QString::number(age)));
            g_Table->setItem(row, table1HeaderList_stu.key("xuehao"), new QTableWidgetItem(gongling));
        }
<<<<<<< HEAD
        else
        {
//            this->slotPageDown();
=======
        if (p_list.size() > 10 && p_list.size() % 10 == 1)
        {
            this->slotPageDown();
>>>>>>> 5a22ea0 (mysql_2)
            //显示下一页
        }
    }
    //添加后清空属性栏内容
    this->lineEditClear();
    this->updateCur();

    this->slotRedirect();
}


/**
 * @brief 删除信息
 */
void XDMFrame::slotDelete()
{
    // 创建一个提示框
    QMessageBox::StandardButton result = QMessageBox::question(this, "用户提示", "请问是否删除？", QMessageBox::Yes | QMessageBox::No);

    if (result == QMessageBox::Yes)
    {
        // 用户点击了"是"按钮，将选中数据删除
        QList<QTableWidgetItem*> selectedItems = g_Table->selectedItems();  // 获取所有被选中的项
        QSet<int> selectedRows;  // 创建一个用于存储选中行的集合
        foreach(QTableWidgetItem* item, selectedItems)  // 遍历所有被选中的项
        {
            selectedRows.insert(item->row());  // 将每个被选中的项的行号插入到集合中
        }
        // 将行号排序，并从最大的行号开始删除
        QList<int> sortedRows = QList<int>::fromSet(selectedRows);  // 将集合转换为列表，这样就可以对行号进行排序
        std::sort(sortedRows.begin(), sortedRows.end(), std::greater<int>());  // 使用std::greater对行号进行降序排序，这样最大的行号会在前面
        foreach(int row, sortedRows)  // 遍历所有行号
        {
            g_Table->removeRow(row);  // 删除每一行
<<<<<<< HEAD

=======
            qDebug() << row;
>>>>>>> 5a22ea0 (mysql_2)
            // 从数据库中删除对应的数据
            if (g_Table == m_pStuTable)
            {
                // 学生表
                const Student& student = s_list.at(row);  // 获取要删除的学生对象
                // 在数据库中执行删除操作
                QSqlQuery query;
                QString deleteQuery = QString("DELETE FROM student WHERE xuehao = %1").arg(student.getXuehao());
                if (!query.exec(deleteQuery))
                {
                    qDebug() << "Failed to delete student from database:" << query.lastError().text();
                    return;  // 执行 SQL 语句失败，退出函数或进行错误处理
                }
<<<<<<< HEAD
                // 从链表中移除该学生对象
                s_list.removeAt(row);
=======
>>>>>>> 5a22ea0 (mysql_2)
            }
            else if (g_Table == m_pProgramTable)
            {
                // 程序员表
                const Programmer& programmer = p_list.at(row);  // 获取要删除的程序员对象
                // 在数据库中执行删除操作
                QSqlQuery query;
                QString deleteQuery = QString("DELETE FROM programmer WHERE gongling = %1").arg(programmer.getGongling());
                if (!query.exec(deleteQuery))
                {
                    qDebug() << "Failed to delete programmer from database:" << query.lastError().text();
                    return;  // 执行 SQL 语句失败，退出函数或进行错误处理
                }
<<<<<<< HEAD
                // 从链表中移除该程序员对象
                p_list.removeAt(row);
=======
>>>>>>> 5a22ea0 (mysql_2)
            }
        }
        this->update();
        this->slotRedirect();
    }
    else
    {
        // 用户点击了"否"按钮，不执行任何操作
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
        if (result == QMessageBox::Yes)
        {

        }
        else
        {
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
//        qDebug() << index;
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
    this->updateCur();
}

<<<<<<< HEAD
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
    this->lineEditClear();
}
=======
//void XDMFrame::slotTableWidgetChange(int index)
//{
////    disconnect(g_Table, &XDMLogTable::sendToXDMF, this, &XDMFrame::slotlineEdit);
////    qDebug() << index;
////    qDebug() << ui->tabWidget->currentIndex();
//    if(ui->tabWidget->currentIndex() == 0)
//    {
//        //修改属性栏
//        ui->comboBox->setCurrentIndex(0);
////        qDebug() << ui->tabWidget->currentIndex();
////        ui->xuehao->setText("学 号：");//重命名学号
////        ui->lineEdit_major->setVisible(true);
////        ui->major->setVisible(true);//重显示专业
////        //更改表格
////        g_Table= m_pStuTable;
////        g_Table->getTableName("s");
//    }
//    else
//    {
//        ui->comboBox->setCurrentIndex(1);
////        ui->xuehao->setText("工 龄：");// 学号修改为工龄
////        ui->lineEdit_major->setVisible(false);
////        ui->major->setVisible(false);//隐藏属性栏专业
////        ui->lineEdit_major->setVisible((false));//隐藏表格专业
////        g_Table = m_pProgramTable;
////        g_Table->getTableName("p");
//     }
//    //table发送信息到Lineedit
////    connect(g_Table, &XDMLogTable::sendToXDMF, this, &XDMFrame::slotlineEdit);
////    this->lineEditClear();
//}
>>>>>>> 5a22ea0 (mysql_2)


/**
 * @brief  分页按钮
 *
 */

//void XDMFrame::slotHomePage()
//{
//    g_Table->clearContents();
//    int row = 0;
//    int all;
////    this->currentPage_1 = 1;
////    this->currentPage_2 = 1;
//    if (ui->tabWidget->currentIndex() == 0)
//    {
//        if (s_list.length() > 9){
//            all = 9;
//        }
//        else{
//            all = s_list.length();
//        }
//        for (int i = 0; i <= all; i++){
//            QTableWidgetItem* item1 = new QTableWidgetItem(s_list[i].name);
//            g_Table->setItem(row, 0, item1);
//            QTableWidgetItem* item2 = new QTableWidgetItem(s_list[i].sex);
//            g_Table->setItem(row, 1, item2);
//            QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(s_list[i].age));
//            g_Table->setItem(row, 2, item3);
//            QTableWidgetItem* item4 = new QTableWidgetItem(s_list[i].getXuehao());
//            g_Table->setItem(row, 3, item4);
//            QTableWidgetItem* item5 = new QTableWidgetItem(s_list[i].getMajor());
//            g_Table->setItem(row, 4, item5);
//            row++;
//        }
//            this->currentPage_1 = 1;
//    }
//    else
//    {
//        if (p_list.length() > 9){
//            all = 9;
//        }
//        else{
//            all = p_list.length();
//        }
//        for (int i = 0; i <= all; i++){
//            QTableWidgetItem* item1 = new QTableWidgetItem(p_list[i].name);
//            g_Table->setItem(row, 0, item1);
//            QTableWidgetItem* item2 = new QTableWidgetItem(p_list[i].sex);
//            g_Table->setItem(row, 1, item2);
//            QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(p_list[i].age));
//            g_Table->setItem(row, 2, item3);
//            QTableWidgetItem* item4 = new QTableWidgetItem(p_list[i].getGongling());
//            g_Table->setItem(row, 3, item4);
//            row++;
//        }
//        this->currentPage_2 = 1;
//    }
//    this->updateCur();

//}


void XDMFrame::slotHomePage()
{
    g_Table->clearContents();
    g_Table->setRowCount(0);
    int all;
<<<<<<< HEAD
    if (ui->tabWidget->currentIndex() == 0)
    {
        all = std::min(9, s_list.size() - 1);
        for (int i = 0; i <= all; i++){
=======
    if (g_Table == m_pStuTable)
    {
        this->currentPage_1 = 1;
        all = std::min(9, s_list.size() - 1);
        for (int i = 0; i <= all; i++){
            int row = g_Table->rowCount();
            g_Table->insertRow(row);
>>>>>>> 5a22ea0 (mysql_2)
            const Student& student = s_list[i]; // 使用引用获取学生对象
            g_Table->setItem(row, 0, new QTableWidgetItem(student.name));
            g_Table->setItem(row, 1, new QTableWidgetItem(student.sex));
            g_Table->setItem(row, 2, new QTableWidgetItem(QString::number(student.age)));
            g_Table->setItem(row, 3, new QTableWidgetItem(student.getXuehao()));
            g_Table->setItem(row, 4, new QTableWidgetItem(student.getMajor()));
<<<<<<< HEAD
            row++;
        }
        this->currentPage_1 = 1;
    }
    else
    {
        all = std::min(9, p_list.size() - 1);
        for (int i = 0; i <= all; i++){
            const Programmer& programmer = p_list[i]; // 使用引用获取程序员对象
            g_Table->setItem(row, 0, new QTableWidgetItem(programmer.name));
            g_Table->setItem(row, 1, new QTableWidgetItem(programmer.sex));
            g_Table->setItem(row, 2, new QTableWidgetItem(QString::number(programmer.age)));
            g_Table->setItem(row, 3, new QTableWidgetItem(programmer.getGongling()));
            row++;
        }
=======
        }
    }
    else
    {
>>>>>>> 5a22ea0 (mysql_2)
        this->currentPage_2 = 1;
        all = std::min(9, p_list.size() - 1);
        for (int i = 0; i <= all; i++){
            int row = g_Table->rowCount();
            g_Table->insertRow(row);
            const Programmer& programmer = p_list[i]; // 使用引用获取程序员对象
            g_Table->setItem(row, 0, new QTableWidgetItem(programmer.name));
            g_Table->setItem(row, 1, new QTableWidgetItem(programmer.sex));
            g_Table->setItem(row, 2, new QTableWidgetItem(QString::number(programmer.age)));
            g_Table->setItem(row, 3, new QTableWidgetItem(programmer.getGongling()));
        }
    }
    this->updateCur();
}




void XDMFrame::slotPageUp()
{
    if (g_Table == m_pProgramTable)
    {
        if (this->currentPage_2 == 1){
            return;
        }
        this->currentPage_2--;
        this->refreshPage();
    }
    else
    {
        if (this->currentPage_1 == 1){
            return;
        }
        this->currentPage_1--;
        this->refreshPage();
    }
    this->updateCur();
}

void XDMFrame::slotPageDown()
{
    this->update();
    if (g_Table == m_pProgramTable)
    {
        if (this->currentPage_2 == this->allPage_2){
            return;
        }
        this->currentPage_2++;
        this->refreshPage();
    }
    else
    {
        if (this->currentPage_1 == this->allPage_1){
            return;
        }
        this->currentPage_1++;
        this->refreshPage();
    }
    this->updateCur();
}

void XDMFrame::slotLastPage()
{
    if (g_Table == m_pProgramTable)
    {
        this->currentPage_2 = this->allPage_2;
        this->refreshPage();
    }
    else
    {
        this->currentPage_1= this->allPage_1;
        this->refreshPage();
    }
    this->updateCur();
}

void XDMFrame::slotRedirect(bool btnClicked)
{
    if (g_Table == m_pProgramTable)
    {
        if (btnClicked == true){
            this->currentPage_2 = ui->gotopage->text().toInt();
        }
        if ((this->currentPage_2 - 1) * 10 == p_list.length()){
            this->currentPage_2--;
        }
        this->refreshPage();
    }
    else
    {
        if (btnClicked == true){
            this->currentPage_1 = ui->gotopage->text().toInt();
        }
        if ((this->currentPage_1 - 1) * 10 == s_list.length()){
            this->currentPage_1--;
        }
        this->refreshPage();
    }
    this->updateCur();
}

void XDMFrame::slotlineEdit(QStringList sl)
{
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
