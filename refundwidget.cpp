//refundwidget.cpp
//Coded by Richard CHEN
//办理退票

#include "refundwidget.h"

RefundWidget::RefundWidget(QWidget *parent) : QWidget(parent)
{
//定义标签并设置其文字
    TitleLabel=new QLabel("REFUND",this);
    IDLabel=new QLabel("ID",this);
    BusNoLabel=new QLabel("Bus No",this);
    DateLabel=new QLabel("Date",this);

//设置TitleLabel的字体大小并设为粗体
    TitleFont.setBold(true);
    TitleFont.setPointSize(20);
    TitleLabel->setFont(TitleFont);

//定义输入框
    IDEdit=new QLineEdit(this);
    BusNoEdit=new QLineEdit(this);
    DateEdit=new QDateEdit(QDate::currentDate(),this);

//对日期输入框的一些设置,由于只发售今明后三天车票，所以设置日期范围为今天~今天+2
    DateEdit->setMinimumDate(QDate::currentDate());
    DateEdit->setMaximumDate(QDate::currentDate().addDays(2));

//定义”保存“和”取消“按钮
    RefundBtn=new QPushButton("Refund",this);
    CancelBtn=new QPushButton("Cancel",this);

//修改窗口大小
    setFixedSize(600,400);

//移动按钮
    RefundBtn->move(275,350);
    CancelBtn->move(450,350);

//移动标签
    const int LabelLocX=50;
    TitleLabel->move(230,25);
    IDLabel->move(LabelLocX,180);
    BusNoLabel->move(LabelLocX,210);
    DateLabel->move(LabelLocX,240);

//移动输入框
    const int LineLocX=350;
    IDEdit->move(LineLocX,180);
    BusNoEdit->move(LineLocX,210);
    DateEdit->move(LineLocX,240);

//点击取消按钮直接退出窗口
    connect(CancelBtn,&QPushButton::clicked,this,&RefundWidget::close);
    connect(RefundBtn,&QPushButton::clicked,this,&RefundWidget::refund);
}
//由于没有直接删除某一行的函数
//所以可以先把一个文件中的所有内容都用一些变量保存
//删掉需要refund的旅客之后，删除原来的文件，再将其他旅客信息写入新文件
void RefundWidget::refund()
{
    QString line;//读入的每一行
    QTextStream input;
    QString idNum=IDEdit->text();//id号
    int num=BusNoEdit->text().toInt();//bus号
    QString date=DateEdit->date().toString("yyyy-MM-dd");//日期
    if(IDEdit->text()==""||BusNoEdit->text()=="")//有空项，提示用户输入信息不完全
    {
        QMessageBox::warning(NULL,"Warning","Information Incomplete.");
    }
    else//没有空项
    {
        QString Filename=QString::number(num)+" "+date+".txt";//文件名为bus班次加上日期
        //首先判断bus是够存在（判断文件是否存在）
        QFile busList(Filename);
        if(!busList.exists())//如果bus不存在
        {
            QMessageBox::warning(NULL,"Warning","This bus doesn't exist.");
        }
        else//bus存在，先判断旅客是否存在
        {
            if(busList.open(QIODevice::ReadWrite))//先打开文件
            {
                bool exist=false;//判断有无这个旅客
                QVector<QString>File;//逐行读入数据，放入File中
                //逐行读入数据
                QTextStream input(&busList);
                QString buf;
                while(!input.atEnd())
                {
                    buf=input.readLine();//按行读入
                    if(buf.indexOf(idNum)>0)//该旅客已经订票了
                    {
                        exist=true;
                    }
                    else
                    {
                        File.push_back(buf);//如果不是这个旅客，将buf放入临时文件中
                    }
                }//读入完成
                if(!exist)//如果没有这个旅客
                {
                    QMessageBox::warning(NULL,"Warning","No such passenger.");
                }
                else//存在该旅客，先删除旧文件，再将之前的信息放入新文件中
                {
                    if(busList.remove())//删除buslist，删除成功为true，否则为false
                    {
                        QFile NewBusList(Filename);
                        NewBusList.open(QIODevice::WriteOnly);
                        NewBusList.close();//先打开，再关闭，以创建文件
                        if(NewBusList.open(QIODevice::WriteOnly))//由于之前已经关闭文件，所以要重新打开，打开同时若打开成功open返回1.否则返回0
                        {
                            QTextStream output(&NewBusList);
                            for(int i=0;i<File.size();i++)
                            {
                                output<<File[i]<<endl;
                            }
                            NewBusList.close();
                            QMessageBox::about(NULL,"Tip","Refund successfully");
                            IDEdit->clear();
                            BusNoEdit->clear();
                            DateEdit->setMinimumDate(QDate::currentDate());
                            DateEdit->setMaximumDate(QDate::currentDate().addDays(2));
                        }
                        else QMessageBox::warning(NULL,"Warning","Failed to open the busList file");
                    }
                    else
                    {
                        QMessageBox::warning(NULL,"Warning","Failed to remove the bus list");
                    }
                }
            }
            else//打开文件失败
            {
                QMessageBox::warning(NULL,"Warning","Failed to open the file.");
            }
        }
    }
}
