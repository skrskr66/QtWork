#ifndef QMUSICWIDGET_H
#define QMUSICWIDGET_H

#include <QWidget>
#include "qvolumewgt.h"
#include "qmusicanimation.h"
#include "qmyanimation.h"
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
    void InitAnimation();
    void SetMusicLyricVec(std::vector<std::string> m_vec){ m_vAllMusicLyric = m_vec; }
private:
    virtual void resizeEvent(QResizeEvent *event);
public slots:
    void OnSlotClickChangeTable();
    void OnSlotUpdatePosition(qint64);
    void OnSlotDurationChanged(qint64);
    void OnSlotCurrentButton(int, QString);
    void OnSlotPlayOrPauseMusic();
    void OnSlotChangeVolume();
    void OnSlotPlayPreviousMusic();
    void OnSlotPlayNextMusic();
    void OnSlotOpenMusicLyircView();
    void OnSlotCloseMusicLryView(bool);
    void OnSlotMusicViewChanged(int);
private:
    Ui::QMusicWidget*               ui;
    QWidget*                        MainWidget;
    QWidget*                        SubWidget;
    QVolumeWgt*                     VolumeWidget;
    int                             m_nIsPlaySta;
    QMyanimation*                   m_nMusicAnimation;   
    std::vector<std::string>        m_vAllMusicLyric;
};

#endif // QMUSICWIDGET_H
