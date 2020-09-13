//mainwidget.cpp
//coded by Richard CHEN
//主窗口
#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
//将其父类定为此窗口，移动label
    welcome=new QLabel("WELCOME",this);
    welcome->move(235,25);
//设置label字体大小，并设为粗体
    welcomeFont.setBold(true);
    welcomeFont.setPointSize(20);
    welcome->setFont(welcomeFont);
//设置窗口标题
    addbuswidget=new AddBusWidget;
    addbuswidget->setWindowTitle("Add Bus Information");
    bookwidget=new BookWidget;
    bookwidget->setWindowTitle("Booking");
    refundwidget=new RefundWidget;
    refundwidget->setWindowTitle("Refund");
    searchbuswidget=new SearchBusWidget;
    searchbuswidget->setWindowTitle("Search a Bus");
    //添加汽车班次按钮
    AddBusBtn=new QPushButton("Add Bus",this);
    //售票按钮
    BookBtn=new QPushButton("Book",this);
    //退票按钮
    RefundBtn=new QPushButton("Refund",this);
    //查找汽车班次的剩余票数和座位号
    SearchBusBtn=new QPushButton("Search",this);
    //退出程序
    QuitBtn=new QPushButton("Quit",this);
//显示各个按钮
    AddBusBtn->show();
    BookBtn->show();
    RefundBtn->show();
    SearchBusBtn->show();
    QuitBtn->show();
//修改窗口大小
    setFixedSize(600,400);
//移动按钮到合适位置
    AddBusBtn->move(250,75);
    BookBtn->move(120,140);
    RefundBtn->move(375,140);
    SearchBusBtn->move(120,210);
    QuitBtn->move(375,210);
//给按钮添加信号
    //使按钮打开指定的窗口
    connect(AddBusBtn,&QPushButton::clicked,addbuswidget,&AddBusWidget::show);
    connect(BookBtn,&QPushButton::clicked,bookwidget,&BookWidget::show);
    connect(RefundBtn,&QPushButton::clicked,refundwidget,&RefundWidget::show);
    connect(SearchBusBtn,&QPushButton::clicked,searchbuswidget,&SearchBusWidget::show);
    //点击”Quit“按钮是窗口关闭
    connect(QuitBtn,&QPushButton::clicked,this,&MainWidget::close);
}

MainWidget::~MainWidget()
{
}
