//searchbuswidget.cpp
//Coded by Richard CHEN
//查询当前指定班次的余票数和座位号

#include "searchbuswidget.h"

SearchBusWidget::SearchBusWidget(QWidget *parent) : QWidget(parent)
{
//新建标签
    TitleLabel=new QLabel("SEARCH",this);
    BusNoLabel=new QLabel("Bus No.",this);
    DateLabel=new QLabel("Date",this);
//设置TitleLabel的字体大小并设为粗体
    TitleFont.setBold(true);
    TitleFont.setPointSize(20);
    TitleLabel->setFont(TitleFont);
//定义输入框
    BusNoEdit=new QLineEdit(this);//班次输入框
    DateEdit=new QDateEdit(QDate::currentDate(),this);//日期输入框，并设置起始日期为今天
//对日期输入框的一些设置,由于只发售今明后三天车票，所以设置日期范围为今天~今天+2
    DateEdit->setMinimumDate(QDate::currentDate());
    DateEdit->setMaximumDate(QDate::currentDate().addDays(2));
//新建”生成“和”取消“按钮
    SearchBtn=new QPushButton("Search",this);
    CancelBtn=new QPushButton("Cancel",this);
//修改窗口大小
    setFixedSize(600,400);
//移动按钮
    SearchBtn->move(275,350);
    CancelBtn->move(450,350);
//移动标签
    const int LabelLocX=50;//Label沿x移动的距离
    TitleLabel->move(230,25);
    BusNoLabel->move(LabelLocX,180);
    DateLabel->move(LabelLocX,220);
//移动输入框
    const int LineLocX=350;
    BusNoEdit->move(LineLocX,180);
    DateEdit->move(LineLocX,220);
//点击取消按钮直接推出窗口
    connect(CancelBtn,&QPushButton::clicked,this,&SearchBusWidget::close);
    connect(SearchBtn,&QPushButton::clicked,this,&SearchBusWidget::search);
}
void SearchBusWidget::search()
{
//获取所有文本框中的值
    int num=BusNoEdit->text().toInt();
    QString Date=DateEdit->date().toString("yyyy-MM-dd");
//如果有缺失信息，弹窗提示用户
    if(BusNoEdit->text()=="")
    {
        QMessageBox::warning(NULL,"Warning","Information incomplete.");
    }
    else
    {
        //首先查找有无这个bus
        QString Filename=QString::number(num)+" "+Date+".txt";//文件名为bus班次加上日期
        QFile busList(Filename);
        if(!busList.exists())//如果bus不存在
        {
            QMessageBox::warning(NULL,"Warning","This bus doesn't exist.");
        }
        else//bus存在，则逐行查找，最终算出余票数和座位号
        {
            if(busList.open(QIODevice::ReadOnly))//先打开文件
            {
                QTextStream input(&busList);
                int max=0;//限乘多少人
                QString _dest,_fn,_ln,_id;//临时存储的信息
                int _seat=0;//临时存储旅客座位号
                int leftnum=0;//有多少没有售出
                input>>max;
                input>>_dest;
                QVector<bool>Sold(max+1,false);

                while(!input.atEnd())
                {
                     input>>_fn>>_ln>>_id>>_seat;
                     qDebug()<<_seat;
                     Sold[_seat]=true;
                 }
                //需要展示在QMessageBox里的信息

                QString outText2=": ";
                for(int i=1;i<Sold.size();i++)
                {
                    if(!Sold[i])
                    {
                        outText2+=QString::number(i)+" ";
                        leftnum++;
                    }
                }
                QString outText1="There are "+QString::number(leftnum)+" seats left";
                QMessageBox::about(NULL,"Tip",outText1+outText2);
                BusNoEdit->clear();
                DateEdit->setMinimumDate(QDate::currentDate());
                DateEdit->setMaximumDate(QDate::currentDate().addDays(2));
            }
            else
            {
                QMessageBox::warning(NULL,"Warning","Failed to open the file.");
            }
        }
    }
}
