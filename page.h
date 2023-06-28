#ifndef PAGE_H
#define PAGE_H

#include <QObject>
#include <QWidget>

class Page : public QWidget
{
    Q_OBJECT
public:
    explicit Page(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // PAGE_H