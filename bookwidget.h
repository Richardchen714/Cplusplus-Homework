//bookwidget.h
//Coded by Richard CHEN
//功能：办理售票
#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector>
#include <random>
#include <ctime>

class BookWidget : public QWidget
{
    Q_OBJECT
private:
//定义标签
    QLabel *TitleLabel;
    QLabel *FNameLabel;
    QLabel *LNameLabel;
    QLabel *IDLabel;
    QLabel *BusNoLabel;
    QLabel *DateLabel;
//输入框
    QLineEdit *FNameEdit;
    QLineEdit *LNameEdit;
    QLineEdit *IDEdit;
    QLineEdit *BusNoEdit;
    QDateEdit *DateEdit;
//定义字体
    QFont TitleFont;
//定义”保存“和”取消“按钮
    QPushButton *SaveBtn;
    QPushButton *CancelBtn;
public:
    explicit BookWidget(QWidget *parent = nullptr);

signals:
public slots:
    void book();
};

#endif // BOOKWIDGET_H
