#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QStyleFactory>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QRgb>
#include <QColor>
#include <QIcon>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void Tran1();
    void Tran2();
    void Tran3();
    void TAllClear();
    void SetButtonColor(int Bcolor);
private:
    Ui::Widget *ui;
    QGridLayout Layout1;
    QLabel L1;
    QLabel L2;
    QLabel L3;
    QLabel L4;
    QPushButton B1;
    QPushButton B2;
    QPushButton B3;
    QPushButton B4;
    QPushButton B5;
    QLineEdit T1;
    QLineEdit T2;
    QLineEdit T3;
    QLineEdit T4;
};

#endif // WIDGET_H
