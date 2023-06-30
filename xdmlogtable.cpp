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

    connect(this, &XDMLogTable::itemSelectionChanged, this, [=](){
        this->list = this->selectedItems();

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
//    QMenu menu(this);
//    QAction *action = menu.addAction("菜单项1");
//    connect(action, &QAction::triggered, this, &XDMLogTable::slotSave);

//    action = menu.addAction("删除");
//    connect(action, &QAction::triggered, this, &XDMLogTable::slotDelete);


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

void XDMLogTable::slotSave()
{
    QString filename = QFileDialog::getSaveFileName(this, "保存", "", "CSV文件 (*.csv)");
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        // 设置编码 仍出现乱码
        stream.setCodec(QTextCodec::codecForUtfText(file.readAll(), QTextCodec::codecForName("UTF-8")));
//        stream.setCodec("UTF-8");
        stream << "姓名,性别,年龄,学号,专业\n";
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


/**
 * @brief 设置填充表格
 * @param header
 */
