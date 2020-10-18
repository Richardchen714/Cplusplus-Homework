//addbuswidget.h
//coded by Richard CHEN
//添加bus信息
#ifndef ADDBUSWIDGET_H
#define ADDBUSWIDGET_H
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QWidget>
#include <QString>
#include <QDateTime>
#include <QFont>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>

class AddBusWidget : public QWidget
{
Q_OBJECT
private:
//定义标签并设置其文字
    QLabel *TitleLabel;
    QLabel *BusNoLabel;
    QLabel *DeptDateTimeLabel;
    QLabel *DestLabel;
    QLabel *SeatNumLabel;
//定义输入框
    QLineEdit *BusNoEdit;
    QDateTimeEdit *DeptDateTimeEdit;
    QLineEdit *DestEdit;
    QLineEdit *SeatNumEdit;
//定义字体
    QFont TitleFont;
//定义保存、取消按钮
    QPushButton *SaveBtn;
    QPushButton *CancelBtn;
public:
    explicit AddBusWidget(QWidget *parent = nullptr);
signals:
public slots:
//添加bus的函数
    void addBus();
};
//定义bus列表保存bus的信息
#endif // ADDBUSWIDGET_H
