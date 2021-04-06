#ifndef RESLIDER_H
#define RESLIDER_H

#include <QSlider>
#include <QMouseEvent>
class ReSlider: public QSlider
{
    Q_OBJECT
public:
    explicit ReSlider(QWidget* parent = NULL);
    ~ReSlider();
protected:
    virtual void mousePressEvent(QMouseEvent* ev);
signals:
    void sgnSwitchMusicPos(int);
};

#endif // RESLIDER_H
