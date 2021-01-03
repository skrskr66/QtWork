#ifndef QVOLUMEWGT_H
#define QVOLUMEWGT_H

#include <QWidget>

namespace Ui {
class QVolumeWgt;
}

class QVolumeWgt : public QWidget
{
    Q_OBJECT

public:
    explicit QVolumeWgt(QWidget *parent = nullptr);
    ~QVolumeWgt();

private:
    virtual void mousePressEvent(QMouseEvent* e);
public:
    void InitStyleSheet();
    void InitVolumeSolider();
signals:
    void sgnSliderMoved(int);
public slots:
    void OnSlotChangeVolumeNum(int);
private:
    Ui::QVolumeWgt *ui;
};

#endif // QVOLUMEWGT_H
