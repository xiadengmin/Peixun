#include "XDMFrame.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QApplication>
#include <QSqlError>

QList<Student> s_list; // 学生链表
QList<Programmer> p_list; // 程序员链表

//// 存储学生链表数据到数据库
//void storeStudentsToDatabase() {
//    QSqlDatabase d  b = QSqlDatabase::database(); // 获取数据库连接

//    // 创建学生表（如果不存在）
//    QSqlQuery createTableQuery("CREATE TABLE IF NOT EXISTS students (name TEXT, sex TEXT, age INTEGER, xuehao TEXT, major TEXT)");
//    if (!createTableQuery.exec()) {
//        qDebug() << "Failed to create students table:" << createTableQuery.lastError().text();
//        return;
//    }

//    // 清空学生表
//    QSqlQuery clearTableQuery("DELETE FROM students");
//    if (!clearTableQuery.exec()) {
//        qDebug() << "Failed to clear students table:" << clearTableQuery.lastError().text();
//        return;
//    }

//    // 将学生链表数据插入到数据库表
//    QSqlQuery insertQuery;
//    insertQuery.prepare("INSERT INTO students (name, sex, age, xuehao, major) VALUES (:name, :sex, :age, :xuehao, :major)");
//    for (const Student& student : s_list) {
//        insertQuery.bindValue(":name", student.name);
//        insertQuery.bindValue(":sex", student.sex);
//        insertQuery.bindValue(":age", student.age);
//        insertQuery.bindValue(":xuehao", student.getXuehao());
//        insertQuery.bindValue(":major", student.getMajor());
//        if (!insertQuery.exec()) {
//            qDebug() << "Failed to insert student data:" << insertQuery.lastError().text();
//            return;
//        }
//    }

//    qDebug() << "Student data stored to database.";
//}

//// 从数据库加载学生数据到链表
//void loadStudentsFromDatabase() {
//    QSqlDatabase db = QSqlDatabase::database(); // 获取数据库连接

//    // 查询学生表
//    QSqlQuery selectQuery("SELECT * FROM students");
//    if (!selectQuery.exec()) {
//        qDebug() << "Failed to execute select query:" << selectQuery.lastError().text();
//        return;
//    }

//    // 清空学生链表
//    s_list.clear();

//    // 逐行读取查询结果并添加到学生链表中
//    while (selectQuery.next()) {
//        Student student;
//        student.name = selectQuery.value("name").toString();
//        student.sex = selectQuery.value("sex").toString();
//        student.age = selectQuery.value("age").toInt();
//        student.setXuehao(selectQuery.value("xuehao").toString());
//        student.setMajor(selectQuery.value("major").toString());
//        s_list.append(student);
//    }

//    qDebug() << "Student data loaded from database.";
//}

//// 从数据库删除学生数据
//void deleteStudentsFromDatabase() {
//    QSqlDatabase db = QSqlDatabase::database(); // 获取数据库连接

//    // 删除学生表中的数据
//    QSqlQuery deleteQuery("DELETE FROM students");
//    if (!deleteQuery.exec()) {
//        qDebug() << "Failed to delete student data:" << deleteQuery.lastError().text();
//        return;
//    }

//    qDebug() << "Student data deleted from database.";
//}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //连接MySQL数据库
    qDebug()<<QSqlDatabase::drivers();
    QString dsn = "Driver={MySQL ODBC 8.0 UniCode Driver};"; // Driver is now {MySQL}
    dsn.append("Server=127.0.0.1,3306;"); // IP,Port
    dsn.append("Uid=root;");           // User
    dsn.append("Pwd=root;");
    dsn.append("MULTI_HOST=1;");

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(dsn);

    if (!db.open())
    {
        qDebug()<<"can't open!"<<db.lastError();
    }
    else
    {
        qDebug()<<"db opened!";
    }

    //    QSqlQuery query(db);
    //    QString s = "select * from user";
    //    query.exec(s);
    //    while (query.next())
    //    {
    //        if (query.value("Db").toString() == "sys");
    //    }



    // 连接成功后

//    // 创建一个查询对象，执行数据库查询
//    QSqlQuery query("SELECT * FROM students");

//    // 执行数据库查询语句
//    QSqlQuery result = db.exec("select table_name from innodb_table_stats;");
//    while (result.next())
//    {
//        qDebug() << result.value("table_name").toString();
//    }



//        // 创建表
//        QSqlQuery query;	// *对数据进行操作所需要使用到的对象*
//        QString sql = "";
//        // 定义sql语句
//        sql = "create table qt_student_table(id int PRIMARY KEY AUTO_INCREMENT, name varchar(32),  sex varchar(32), agg int,  xuehao varchar(32), major varchar(32  ));";
//        // 执行sql语句
//        query.exec(sql);

    QSqlQuery query;

    // 创建数据库
    QString createDatabase = "CREATE DATABASE IF NOT EXISTS peixun;";
    if (!query.exec(createDatabase)) {
        qDebug() << "Failed to create database:" << query.lastError().text();
        return -1; // 执行 SQL 语句失败，退出程序或进行错误处理
    }

    // 选择数据库
    QString useDatabase = "USE peixun;";
    if (!query.exec(useDatabase)) {
        qDebug() << "Failed to use database:" << query.lastError().text();
        return -1; // 执行 SQL 语句失败，退出程序或进行错误处理
    }

    // 创建 student 表
    QString createStudentTable = "CREATE TABLE IF NOT EXISTS student ("
                                 "id INT PRIMARY KEY AUTO_INCREMENT,"
                                 "name VARCHAR(32),"
                                 "sex VARCHAR(10),"
                                 "age INT,"
                                 "xuehao VARCHAR(32),"
                                 "major VARCHAR(50)"
                                 ")";
    if (!query.exec(createStudentTable)) {
        qDebug() << "Failed to create student table:" << query.lastError().text();
        return -1; // 执行 SQL 语句失败，退出程序或进行错误处理
    }

    // 创建 programmer 表
    QString createProgrammerTable = "CREATE TABLE IF NOT EXISTS programmer ("
                                    "id INT PRIMARY KEY AUTO_INCREMENT,"
                                    "name VARCHAR(32),"
                                    "sex VARCHAR(10),"
                                    "age INT,"
                                    "gongling VARCHAR(50)"
                                    ")";
    if (!query.exec(createProgrammerTable)) {
        qDebug() << "Failed to create programmer table:" << query.lastError().text();
        return -1; // 执行 SQL 语句失败，退出程序或进行错误处理
    }

    //数据库连接链表

    // 将s_list中的数据插入student表格
    foreach (const Student& student, s_list) {
        QString insertStudentQuery = QString("INSERT INTO student (name, sex, age, xuehao, major) "
                                             "VALUES ('%1', '%2', %3, '%4', '%5')")
                                             .arg(student.getName())
                                             .arg(student.getSex())
                                             .arg(student.getAge())
                                             .arg(student.getXuehao())
                                             .arg(student.getMajor());
        QSqlQuery insertStudent(db);
        if (!insertStudent.exec(insertStudentQuery)) {
            qDebug() << "Failed to insert student data:" << insertStudent.lastError().text();
            return 1;
        }
    }



    XDMFrame w;
//    w.showMaximized();
    w.show();

    return a.exec();
}
