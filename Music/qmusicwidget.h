#ifndef QMUSICWIDGET_H
#define QMUSICWIDGET_H

#include <QWidget>
#include "qvolumewgt.h"
namespace Ui {
class QMusicWidget;
}

class QMusicWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QMusicWidget(QWidget *parent = nullptr);
    ~QMusicWidget();
    void InitInterface();
    void InitButton();
    void InitStackedWidget();
    void InitSlider();

public slots:
    void OnSlotClickChangeTable();
    void OnSlotUpdatePosition(qint64);
    void OnSlotDurationChanged(qint64);
    void OnSlotCurrentButton(int);
    void OnSlotPlayOrPauseMusic();
    void OnSlotChangeVolume();
private:
    Ui::QMusicWidget*               ui;
    QWidget*                        MainWidget;
    QWidget*                        SubWidget;
    QVolumeWgt*                     VolumeWidget;
    int                             m_nIsPlaySta;
};

#endif // QMUSICWIDGET_H
