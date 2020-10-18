//bookwidget.cpp
//Coded by Richard CHEN
//办理售票
#include "bookwidget.h"

BookWidget::BookWidget(QWidget *parent) : QWidget(parent)
{
//设置标签的文字
    TitleLabel=new QLabel("BOOKING",this);
    FNameLabel=new QLabel("First Name",this);
    LNameLabel=new QLabel("Last Name",this);
    IDLabel=new QLabel("ID",this);
    BusNoLabel=new QLabel("Bus No",this);
    DateLabel=new QLabel("Date",this);
//设置TitleLabel的字体大小并设为粗体
    TitleFont.setBold(true);
    TitleFont.setPointSize(20);
    TitleLabel->setFont(TitleFont);
//输入框
    FNameEdit=new QLineEdit(this);
    LNameEdit=new QLineEdit(this);
    IDEdit=new QLineEdit(this);
    BusNoEdit=new QLineEdit(this);
    DateEdit=new QDateEdit(QDate::currentDate(),this);
//对日期输入框的一些设置,由于只发售今明后三天车票，所以设置日期范围为今天~今天+2
    DateEdit->setMinimumDate(QDate::currentDate());
    DateEdit->setMaximumDate(QDate::currentDate().addDays(2));
//定义”保存“和”取消“按钮
    SaveBtn=new QPushButton("Book",this);
    CancelBtn=new QPushButton("Cancel",this);
//修改窗口大小
    setFixedSize(600,400);
//移动按钮
    SaveBtn->move(275,350);
    CancelBtn->move(450,350);
//移动标签
    const int LabelLocX=50;
    TitleLabel->move(230,25);
    FNameLabel->move(LabelLocX,120);
    LNameLabel->move(LabelLocX,150);
    IDLabel->move(LabelLocX,180);
    BusNoLabel->move(LabelLocX,210);
    DateLabel->move(LabelLocX,240);
//移动输入框
    const int LineLocX=350;
    FNameEdit->move(LineLocX,120);
    LNameEdit->move(LineLocX,150);
    IDEdit->move(LineLocX,180);
    BusNoEdit->move(LineLocX,210);
    DateEdit->move(LineLocX,240);
//点击取消按钮直接退出窗口，点击book按钮预定
    connect(CancelBtn,&QPushButton::clicked,this,&BookWidget::close);
    connect(SaveBtn,&QPushButton::clicked,this,&BookWidget::book);
}
void BookWidget::book()
{
    QString fn=FNameEdit->text();
    QString ln=LNameEdit->text();
    QString id=IDEdit->text();
    int busNo=BusNoEdit->text().toInt();
    QDate date=DateEdit->date();
    if(fn==""||ln==""||id==""||BusNoEdit->text()=="")//有空项，提示用户输入信息不完全
    {
        QMessageBox::warning(NULL,"Warning","Information Incomplete.");
    }
    else//首先需要检查bus是否存在，不存在提示用户
    {
        QString Filename=QString::number(busNo)+" "+date.toString("yyyy-MM-dd")+".txt";//文件名为bus班次加上日期
        QFile busList(Filename);
        if(!busList.exists())//如果bus不存在
        {
            QMessageBox::warning(NULL,"Warning","This bus doesn't exist.");
        }
        else//bus存在
        {
            //先查找该旅客是否已经订了票（即查找id相同的旅客）、bus是不是已经满了
            //因为前两行不可能含有旅客id，所以正常处理
            if(busList.open(QIODevice::ReadWrite))//先打开文件
            {
                QTextStream input(&busList);
                bool booked=false;//旅客有无订过票
                int sold=0;//售出票数
                int max=0;//限乘多少人
                int _seat=0;//读入的旅客的座位号临时存储在这里
                QString _fn,_ln,_id,_dest;//需要从文档里面读入的数据
                input>>max;//第一行为座位数，即限制乘坐的人数
                input>>_dest;//第二行为目的地
                QVector<bool>Sold(max+1,false);//构建一个数组判断每个座位是不是已经售出，并将所有元素都初始化为false
                while(!input.atEnd())
                {
                    input>>_fn>>_ln>>_id>>_seat;//读入
                    Sold[_seat]=true;//将这个旅客的座位号标记为已售出
                    sold++;//售出的票数++
                    if(_id==id)//存在这个旅客（id出现在旅客列表里面了）
                    {
                        booked=true;//该旅客已订
                    }
                }
                int seatNum=0;//该旅客的座位号
                int tmp;//用来临时存储生成的随机数
                if(sold==max)//已经满了
                {
                    QMessageBox::warning(NULL,"Warning","This bus is full.");
                }
                else if(booked)//旅客已订票
                {
                    QMessageBox::warning(NULL,"Warning","This passenger has already booked");
                }
                else//其他情况，旅客可以订票，将旅客信息写入乘客名单中，写入信息依次为依次为旅客first name, last name, id num, seat num
                {
                    //首先随机生成一个座位号
                    std::default_random_engine engine(time(0));
                    std::uniform_int_distribution<unsigned int>randomInt(1, max);//随机生成一个1-max的数字
                    while(1)
                    {
                        //临时存储
                        tmp=randomInt(engine);
                        if(!Sold[tmp])//如果这个座位没有售出，那这就是该旅客的座位号，退出循环
                        {
                            seatNum=tmp;
                            break;
                        }
                    }
                    //在文件中写入旅客信息
                    QTextStream output(&busList);//此时文件已经打开，无需再次打开
                    output<<endl<<fn<<" "<<ln<<" "<<id<<" "<<QString::number(seatNum);//写入旅客信息。其中的座位号转化为QString防止输入乱码
                    QMessageBox::about(NULL,"Tip","Booked successfully");
                }
                //最后清空对话框,日期对话框恢复
                FNameEdit->clear();
                LNameEdit->clear();
                IDEdit->clear();
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
