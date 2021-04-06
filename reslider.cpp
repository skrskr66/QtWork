#include "reslider.h"


ReSlider::ReSlider(QWidget* parent)
    :QSlider(parent)
{

}

ReSlider::~ReSlider()
{

}

void ReSlider::mousePressEvent(QMouseEvent* ev)
{
    QSlider::mousePressEvent(ev);//要先调用父类的鼠标点击事件，为了不影响拖动的情况
    //时刻获取鼠标的位置
    double pos = ev->pos().x() / (double)width();
    double val = pos * (maximum() - minimum()) + minimum();

    setValue(val + 0.5);//为了四舍五入+0.5

    emit sgnSwitchMusicPos(val + 0.5);
}

