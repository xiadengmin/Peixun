#ifndef XDMLOGTABLE_H
#define XDMLOGTABLE_H

#include <QWidget>
#include <QTableWidget>


/**
 * @brief 自定义表格，用于封装不同职业的信息显示表格
 */
class XDMLogTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit XDMLogTable(QWidget *parent = nullptr);
    ~XDMLogTable();

    void setHeaderList(QStringList header);

signals:

public slots:

};

#endif // XDMLOGTABLE_H
