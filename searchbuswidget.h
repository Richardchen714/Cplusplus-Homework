#ifndef SEARCHBUSWIDGET_H
#define SEARCHBUSWIDGET_H
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include "addbuswidget.h"

class SearchBusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchBusWidget(QWidget *parent = nullptr);
private:
    QLabel *TitleLabel;
    QLabel *BusNoLabel;
    QLabel *DateLabel;
    QFont TitleFont;
    QLineEdit *BusNoEdit;
    QDateEdit *DateEdit;
    QPushButton *SearchBtn;
    QPushButton *CancelBtn;
signals:
public slots:
    void search();
};

#endif // SEARCHBUSWIDGET_H
