#include "qmyanimation.h"
#include <QPropertyAnimation>
#include <QDebug>
QMyanimation::QMyanimation(QObject *parent)
    : QObject(parent)
{

}


void QMyanimation::setAnimationWgt(QWidget *pParentWgt, QWidget* pSubWgt)
{
    if(nullptr == pParentWgt || nullptr == pSubWgt)
    {
        return;
    }
    m_ParentWgt = pParentWgt;
    m_SubWgt = pSubWgt;
}

void QMyanimation::StartAnimation(bool bShow)
{
    if(nullptr == m_ParentWgt || nullptr == m_SubWgt)
    {
        return;
    }

    QPropertyAnimation* animation = new QPropertyAnimation(m_SubWgt, "geometry");
    QRect rcBegin;
    QRect rcEnd;
    getAniamtionGeometry(rcBegin, rcEnd, bShow);
    qDebug()<<rcBegin<<endl;
    qDebug()<<rcEnd<<endl;
    animation->setStartValue(rcBegin);
    animation->setEndValue(rcEnd);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void QMyanimation::getAniamtionGeometry(QRect &RcBegin, QRect &RcEnd, bool IsShow)
{
    if(nullptr == m_ParentWgt || nullptr == m_SubWgt)
    {
        return;
    }
    if(IsShow)
    {
        RcBegin = QRect(0,m_ParentWgt->height(),m_ParentWgt->width(),m_ParentWgt->height());
        RcEnd = QRect(0, 0, m_ParentWgt->width(),m_ParentWgt->height());
    }
    else
    {
        RcBegin = QRect(0, 0, m_ParentWgt->width(),m_ParentWgt->height());
        RcEnd = QRect(0,m_ParentWgt->height(),m_ParentWgt->width(),m_ParentWgt->height());
    }
}
