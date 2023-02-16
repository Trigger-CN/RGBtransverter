#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle(tr("RGBTransverterV1.0"));
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0xff,0xff,0xff,0xff));
    setPalette(pal);
    //setWindowOpacity(0.8);
    setWindowFlags(windowFlags()
                   &~Qt::WindowCloseButtonHint
                   &~Qt::WindowMinimizeButtonHint
                   &~Qt::WindowMaximizeButtonHint
);
    setWindowFlags(windowFlags()
                   |Qt::WindowStaysOnTopHint
);



    L1.setParent(this);
    L1.setText("RGBweb");
    L1.move(20,13);

    L2.setParent(this);
    L2.setText("RGB565");
    L2.move(20,73);

    L3.setParent(this);
    L3.setText("RGB888");
    L3.move(20,43);

    L4.setParent(this);
    L4.setText("BGR565XOR");
    L4.move(10,103);

    B1.setParent(this);
    B1.setText("  ");
    B1.move(270,10);

//    B2.setParent(this);
//    B2.setText("转换");
//    B2.move(250,40);

    B3.setParent(this);
    B3.setText("  ");
    B3.move(270,40);

    B4.setParent(this);
    B4.setText("清空");
    B4.move(270,70);

    B5.setParent(this);
    B5.setText("退出");
    B5.move(270,100);



    T1.setParent(this);
    T1.move(80,10);
    T1.setMaxLength(9);
    T1.setInputMask("000,000,000");

    T2.setParent(this);
    T2.move(80,70);
    //T2.setMaxLength(4);

    T3.setParent(this);
    T3.move(80,40);
    //T3.setMaxLength(6);

    T4.setParent(this);
    T4.move(80,100);
    T4.setAutoFillBackground(true);
    //connect(&B1,&QPushButton::pressed,this,&Widget::Tran1);
    //connect(&B2,&QPushButton::pressed,this,&Widget::Tran2);
    //connect(&B3,&QPushButton::pressed,this,&Widget::Tran3);
    connect(&B4,&QPushButton::pressed,this,&Widget::TAllClear);
    connect(&B5,&QPushButton::pressed,this,&Widget::close);
    connect(&T1,&QLineEdit::returnPressed,this,&Widget::Tran1);
    connect(&T2,&QLineEdit::returnPressed,this,&Widget::Tran2);
    connect(&T3,&QLineEdit::returnPressed,this,&Widget::Tran3);
    resize(400,150);


}

Widget::~Widget()
{
    delete ui;
}
void Widget::Tran1()
{
    //bool ok;
    int R,G,B;
    int _B,_G,_R;
    QString str = T1.text();
    char *ch;
    QByteArray ba = str.toLatin1();
    ch = ba.data();
    sscanf(ch,"%d,%d,%d",&R,&G,&B);

    //QRgb RGBweb = qRgb(R,G,B);//0xAARRGGBB

    int Rgb888 = (R<<16)|(G<<8)|B;//0xRRGGBB,RGB888
    int Rgb565_H = (R&0xf8)|((G&0xe0)>>5);
    int Rgb565_L = ((G&0x1c)<<3)|((B&0xf8)>>3);
    int Rgb565 = (Rgb565_H<<8)|Rgb565_L;

    _B = Rgb888>>16;
    _G = (Rgb888>>8)&0xff;
    _R = Rgb888&0xff;
    int Bgr565_H = (_R&0xf8)|((_G&0xe0)>>5);
    int Bgr565_L = ((_G&0x1c)<<3)|((_B&0xf8)>>3);
    int Bgr565 = (Bgr565_H<<8)|Bgr565_L;
    int Bgr565XOR = Bgr565^0xffff;

    T2.setText(QString::number(Rgb565,16));
    T3.setText(QString::number(Rgb888,16));
    T4.setText(QString::number(Bgr565XOR,16));
    Widget::SetButtonColor(Rgb888);
    //qDebug()<<R<<G<<B<<Rgb888<<Rgb565_H<<Rgb565_L;
}
void Widget::Tran2()
{
    bool ok;
    QString str1 = T2.text();
    int RGB565 = str1.toInt(&ok,16);
    int RGB565_R = RGB565>>11;
    int RGB565_G = (RGB565>>5)&0x3f;
    int RGB565_B = RGB565&0x1f;
    int BGR565 = (RGB565_B<<11)|(RGB565_G<<5)|(RGB565_R);
    int BGR565XOR = BGR565^0xffff;
    T4.setText(QString::number(BGR565XOR,16));
    //qDebug()<<RGB565_R<<RGB565_G<<RGB565_B;
}
void Widget::Tran3()
{
    int R,G,B;
    int _B,_G,_R;
    bool ok;
    char str1[100];
    QString str2 = T3.text();
    int a = str2.toInt(&ok,16);
    R = a>>16;
    G = (a>>8)&0xff;
    B = a&0xff;
//0xRRGGBB,RGB888
    int Rgb565_H = (R&0xf8)|((G&0xe0)>>5);
    int Rgb565_L = ((G&0x1c)<<3)|((B&0xf8)>>3);
    int Rgb565 = (Rgb565_H<<8)|Rgb565_L;

    _B = a>>16;
    _G = (a>>8)&0xff;
    _R = a&0xff;
    int Bgr565_H = (_R&0xf8)|((_G&0xe0)>>5);
    int Bgr565_L = ((_G&0x1c)<<3)|((_B&0xf8)>>3);
    int Bgr565 = (Bgr565_H<<8)|Bgr565_L;

    sprintf(str1,"%d,%d,%d",R,G,B);
    int Bgr565XOR = Bgr565^0xffff;
    T1.setText(str1);
    T2.setText(QString::number(Rgb565,16));
    T4.setText(QString::number(Bgr565XOR,16));
    Widget::SetButtonColor(a);
}
void Widget::TAllClear()
{
    T1.clear();
    T2.clear();
    T3.clear();
    T4.clear();
    Widget::SetButtonColor(0);
}
void Widget::SetButtonColor(int Bcolor)
{
    QPalette pal1 = B1.palette();
    pal1.setColor(QPalette::Button,Bcolor);

    B1.setAutoFillBackground(true);
    B1.setFlat(true);
    B1.setPalette(pal1);

    QPalette pal2 = B3.palette();
    pal2.setColor(QPalette::Button,Bcolor);

    B3.setAutoFillBackground(true);
    B3.setFlat(true);
    B3.setPalette(pal2);
}
