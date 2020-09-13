//addbuswidget.cpp
//Coded by Richard CHEN
//添加bus信息
#include "addbuswidget.h"

AddBusWidget::AddBusWidget(QWidget *parent) : QWidget(parent)
{
//窗口的一些基本设置
//设置标签文字
    TitleLabel=new QLabel("ADD A BUS",this);//窗口标题
    BusNoLabel=new QLabel("Bus No.",this);//班次
    DeptDateTimeLabel=new QLabel("Depature Date&Time",this);//日期
    DestLabel=new QLabel("Destination",this);//目的地
    SeatNumLabel=new QLabel("Seat Number",this);//座位数量
//设置TitleLabel的字体大小并设为粗体
    TitleFont.setBold(true);
    TitleFont.setPointSize(20);
    TitleLabel->setFont(TitleFont);
//定义输入框
    BusNoEdit=new QLineEdit(this);//班次输入框
    DeptDateTimeEdit=new QDateTimeEdit(QDateTime::currentDateTime(),this);//日期输入框，并设置起始日期为今天
    DestEdit=new QLineEdit(this);//目的地输入框
    SeatNumEdit=new QLineEdit(this);//座位数量输入框
//对日期输入框的一些设置,由于只发售今明后三天车票，所以设置日期范围为今天~今天+2
    DeptDateTimeEdit->setMinimumDate(QDate::currentDate());
    DeptDateTimeEdit->setMaximumDate(QDate::currentDate().addDays(2));
//定义”保存“和”取消“按钮
    SaveBtn=new QPushButton("Save",this);
    CancelBtn=new QPushButton("Cancel",this);
//修改窗口大小
    setFixedSize(600,400);
//移动按钮
    SaveBtn->move(275,350);
    CancelBtn->move(450,350);
//移动标签
    const int LabelLocX=50;//Label沿x移动的距离
    TitleLabel->move(230,25);
    BusNoLabel->move(LabelLocX,120);
    DeptDateTimeLabel->move(LabelLocX,150);
    DestLabel->move(LabelLocX,180);
    SeatNumLabel->move(LabelLocX,210);
//移动输入框
    const int LineLocX=350;
    BusNoEdit->move(LineLocX,120);
    DeptDateTimeEdit->move(LineLocX,150);
    DestEdit->move(LineLocX,180);
    SeatNumEdit->move(LineLocX,210);
//点击取消按钮直接退出窗口，点击保存按钮保存信息
    connect(CancelBtn,&QPushButton::clicked,this,&AddBusWidget::close);
    connect(SaveBtn,&QPushButton::clicked,this,&AddBusWidget::addBus);
}

//添加bus的函数
void AddBusWidget::addBus()
{
//获取所有文本框中的值
    int num=BusNoEdit->text().toInt();
    QString dest=DestEdit->text();
    QDateTime datetime=DeptDateTimeEdit->dateTime();
    int seat=SeatNumEdit->text().toInt();
//如果有缺失信息，弹窗提示用户
    if(BusNoEdit->text()==""||DestEdit->text()==""||SeatNumEdit->text()=="")
    {
        QMessageBox::warning(NULL,"Warning","Information incomplete.");
    }
    else//否则需要先查找这个bus是否已经存在，如果存在，创建这个bus的乘客列表
    {
        //补充：一个busList的格式：第一行为座位数，第二行为目的地，第三行之后依次为旅客first name, last name, id num, seat num
        QString Filename=QString::number(num)+" "+datetime.date().toString("yyyy-MM-dd")+".txt";//文件名为bus班次加上日期
        //由于此处已经将busList创建，所以不需要printOneBusList的功能（输出指定班次的旅客登记表，发车前交驾驶员用）
        QFile busList(Filename);//在"build-BusBookingSystem02-Desktop_x86_windows_msvc2019_pe_32bit-Debug"文件夹中创建了bus.txt文件
        if(busList.exists())
        {
            QMessageBox::warning(NULL,"Warning","This bus exists.");
        }
        else
        {
            busList.open(QIODevice::WriteOnly);
            busList.close();//先打开，再关闭，以创建文件
            QMessageBox::about(NULL,"Tip","Bus added.");
            //在busList写入：第一行座位数，第二行目的地
            if(busList.open(QIODevice::WriteOnly))//由于之前已经关闭文件，所以要重新打开，打开同时若打开成功open返回1.否则返回0
            {
                QTextStream stream(&busList);
                stream<<QString::number(seat)<<endl<<dest;//将数字转化为字符防止乱码
                busList.close();//重新关闭文件
            }
            else QMessageBox::warning(NULL,"Warning","Failed to open the busList file");
        }
        //最后需要清空输出输入框,时间的输入输出框复位
        BusNoEdit->clear();
        DeptDateTimeEdit->setMinimumDate(QDate::currentDate());
        DeptDateTimeEdit->setMaximumDate(QDate::currentDate().addDays(2));
        DestEdit->clear();
        SeatNumEdit->clear();
    }
}
