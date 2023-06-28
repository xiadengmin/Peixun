#include "XDMFrame.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QApplication>
#include <QSqlError>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //连接MySQL数据库
    qDebug()<<QSqlDatabase::drivers();
    QString dsn = "Driver={MySQL ODBC 8.0 UniCode Driver};"; // Driver is now {MySQL}
    dsn.append("Server=127.0.0.1,3306;"); // IP,Port
    dsn.append("Database=mysql;");  // Schema
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
        qDebug()<<"open!";
    }

    QSqlQuery result = db.exec("select user from user;");
    while (result.next())
    {
        qDebug() << result.value("user").toString();
    }


    XDMFrame w;
    w.showMaximized();

    return a.exec();
}
