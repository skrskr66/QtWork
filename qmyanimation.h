#ifndef QMYANIMATION_H
#define QMYANIMATION_H

#include <QObject>
#include <QWidget>
class QMyanimation : public QObject
{
    Q_OBJECT
public:
    explicit QMyanimation(QObject *parent = nullptr);
    void setAnimationWgt(QWidget* pParentWgt, QWidget* pSubWgt);
    void StartAnimation(bool bShow = true);
    void getAniamtionGeometry(QRect& RcBegin,QRect& RcEnd,bool IsShow);
signals:

public slots:

private:
    QWidget* m_ParentWgt;
    QWidget* m_SubWgt;
};

#endif // QMYANIMATION_H
