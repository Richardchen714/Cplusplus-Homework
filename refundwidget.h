//refundwidget.h
//Coded by Richard CHEN
//办理退票
#ifndef REFUNDWIDGET_H
#define REFUNDWIDGET_H
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QLineEdit>
#include <QDateEdit>
#include <QWidget>
#include <QTextStream>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QVector>

class RefundWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RefundWidget(QWidget *parent = nullptr);
private:
    //标签，只需要输入旅客id、bus号和日期
    QLabel *TitleLabel;
    QLabel *IDLabel;
    QLabel *BusNoLabel;
    QLabel *DateLabel;
    QFont TitleFont;
    QLineEdit *IDEdit;
    QLineEdit *BusNoEdit;
    QDateEdit *DateEdit;
    QPushButton *RefundBtn;
    QPushButton *CancelBtn;
signals:
public slots:
    void refund();
};

#endif // REFUNDWIDGET_H
