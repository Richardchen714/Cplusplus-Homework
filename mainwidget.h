//mainwidget.h
//Coded by Richard CHEN
#ifndef WIDGET_H
#define WIDGET_H
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QWidget>
#include <QDebug>
#include <QDir>
#include "addbuswidget.h"
#include "bookwidget.h"
#include "refundwidget.h"
#include "searchbuswidget.h"
class MainWidget : public QWidget
{
    Q_OBJECT
private:
//定义一个”欢迎“的label
    QLabel *welcome;
//定义窗口
    AddBusWidget *addbuswidget;
    BookWidget *bookwidget;
    RefundWidget *refundwidget;
    SearchBusWidget *searchbuswidget;
//定义字体
    QFont welcomeFont;
//定义按钮
    QPushButton *AddBusBtn;
    QPushButton *BookBtn;
    QPushButton *RefundBtn;
    QPushButton *SearchBusBtn;
    QPushButton *QuitBtn;
//定义一个数据库

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
};
#endif // WIDGET_H
