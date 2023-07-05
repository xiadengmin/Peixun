#include "xdmlogtable.h"

#include <QHeaderView>
#include <QAction>
#include <QMenu>

#include <QContextMenuEvent>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextCodec>
XDMLogTable::XDMLogTable(QWidget *parent) : QTableWidget(parent)
{
    horizontalHeader()->setVisible(true);
    verticalHeader()->setVisible(true);


    connect(this, &XDMLogTable::itemSelectionChanged, this, [=]()
    {
        this->list = this->selectedItems();

        QStringList sl;
        // 获取当前选中行的项
        int currentRow = XDMLogTable::currentRow(); // 获取当前选中行的索引
        for(int col = 0; col < XDMLogTable::columnCount(); col++)
        {
            QTableWidgetItem* item = XDMLogTable::item(currentRow, col); // 获取当前行的每一列的项
            if(item)
            {
                QString text = item->text(); // 获取项的文本
                sl << text;
            }
        }
        qDebug() << sl;
        emit this->sendToXDMF(sl);


//        if (!this->list.isEmpty())
//        {
//            // 获取当前选中的行
//            int row = this->list.first()->row();
//            // 更新属性栏的值，属性栏由QLineEdit组成
//            lineEdit_gname->setText(this->item(row, 0)->text());
//            lineEdit_gsex->setText(this->item(row, 1)->text());


//        }

    });
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

void XDMLogTable::contextMenuEvent(QContextMenuEvent *e)
{
    QMenu menu(this);

    QAction *saveAction = new QAction("保存为文件", this);
    connect(saveAction, &QAction::triggered, this, &XDMLogTable::slotSave);
    menu.addAction(saveAction);

    QAction *deleteAction = new QAction("删除", this);
    connect(deleteAction, &QAction::triggered, this, &XDMLogTable::slotDelete);
    menu.addAction(deleteAction);

    QPoint p = e->pos();
    p.setY(p.y() + 30);
    menu.exec(mapToGlobal(p));
}

/**
 * @brief 接收XDMFrame中的g_table
 */
void XDMLogTable::getTableName(QString str)
{
    this->tableName = str;
}

//void XDMLogTable::getLineEdit(QLineEdit mm)
//{
//    this->lineEdit_gname = mm;
//    this->lineEdit_gsex = mm;
//    this->lineEdit_gage = mm;
//    this->lineEdit_gxuehao = mm;
//    this->lineEdit_gmajor = mm;

//}

void XDMLogTable::slotSave()
{
    QString filename = QFileDialog::getSaveFileName(this, "保存", "", "CSV文件 (*.csv)");
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        // 设置编码 表头仍出现乱码
        if(tableName == "p")
        {
            stream << "name,sex,age,gongling\n";
        }
        else
        {
            stream << "name,sex,age,xuehao,major\n";
        }
        stream.setCodec("UTF-8");
//        stream << "name,sex,age,xuehao,major\n";

        int r = this->list.size() / this->columnCount(); // 计算列数
        int i = 0;
        for (int row = 0; row < r; ++row)
        {
            for (int column = 0; column < this->columnCount(); ++column)
            {
                QTableWidgetItem *item = this->list.at(i);
                if (!item || item->text().isEmpty()) // 确保项不为空且不是空字符串
                {
                    stream << ",";
                }
                else
                {
                    stream << item->text() << ",";
                }
                i++;
            }
            stream << "\n";
        }
    }

    file.close();
}

void XDMLogTable::slotDelete()
{
    // 创建一个提示框
    QMessageBox::StandardButton result = QMessageBox::question(this, "用户提示", "请问是否删除？", QMessageBox::Yes | QMessageBox::No);

    // 处理用户的选择
    if (result == QMessageBox::Yes)
    {
        // 用户点击了"是"按钮，将选中数据删除
//        QList<QTableWidgetItem*> selectedItems = g_Table->selectedItems();
        QSet<int> selectedRows;
        foreach(QTableWidgetItem* item, this->list) {
            selectedRows.insert(item->row());
        }
        QList<int> sortedRows = QList<int>::fromSet(selectedRows);
        std::sort(sortedRows.begin(), sortedRows.end(), std::greater<int>());
        foreach(int row, sortedRows) {
            this->removeRow(row);
        }
    }
}


