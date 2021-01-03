#ifndef FAVORITEWIDGET_H
#define FAVORITEWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>
#include "muiscstyleditemdelegate.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSqlDatabase>
#include <QSqlQuery>
namespace Ui {
class FavoriteWidget;
}

#define BUTTON_CURRENT_PLAY 1
#define BUTTON_CURRENT_PAUSE 0

class FavoriteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FavoriteWidget(QWidget *parent = nullptr);
    ~FavoriteWidget();
    void InitInterface();
    void InitStackedWidget();
    void InitTableWidget();
    void InitMusicList();
    void InitDataBase();

public:
    //virtual void mouseMoveEvent(QMouseEvent* event);
    //virtual void leaveEvent(QEvent* event);
    void PauseOrPlayMusic();

signals:
    void sgnPositionChanged(qint64);
    void sgnDurationChanged(qint64);
    void sgnCurrentplaybutton(int);
public slots:
    void onSlotClickChangeTable();
    void onSlotTableClicked(const QModelIndex&);
    void OnSlotColtrolvolume(int);
private:
    Ui::FavoriteWidget*         ui;
    QSqlTableModel*             m_pModel;
    MuiscStyledItemDelegate*    m_pMusicDelegate;
    QMediaPlaylist*             m_pPlayList;
    QMediaPlayer*               m_pMusicPlayer;
    QSqlDatabase                m_pMusicDataBase;
};

#endif // FAVORITEWIDGET_H
