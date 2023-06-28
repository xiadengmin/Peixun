#include "xdmlogtable.h"

#include <QHeaderView>

XDMLogTable::XDMLogTable(QWidget *parent) : QTableWidget(parent)
{
    horizontalHeader()->setVisible(true);
    verticalHeader()->setVisible(true);
}

XDMLogTable::~XDMLogTable()
{

}

/**
 * @brief 设置表格表头
 * @param header
 */
void XDMLogTable::setHeaderList(QStringList header)
{
    setColumnCount(header.count());
    setHorizontalHeaderLabels(header);
}


/**
 * @brief 设置填充表格
 * @param header
 */
