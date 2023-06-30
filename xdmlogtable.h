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

    void contextMenuEvent(QContextMenuEvent *e);

signals:

public slots:
    void slotSave();
    void slotDelete();

private:
    QList<QTableWidgetItem *> list;
};

#endif // XDMLOGTABLE_H
