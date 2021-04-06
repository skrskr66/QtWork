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
#include <QMenu>
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
    void HandleMusicTable();
public:
    void PauseOrPlayMusic();
    void PlaypPreviousMusic();
    void PlayNextMusic();
    void Do(QAction* ActionVal);
    std::vector<std::string> GetMusicLyirc(){ return m_vMusicLyric; }
signals:
    void sgnPositionChanged(qint64);
    void sgnDurationChanged(qint64);
    void sgnCurrentplaybutton(int, QString);
    void sgnMusicViewChanged(int);
public slots:
    void onSlotClickChangeTable();
    void onSlotTableClicked(const QModelIndex&);
    void OnSlotColtrolvolume(int);
    void OnSlotSwitchPosition(int);
    void OnSlotPlayNextMusic();
    void OnSlotRClickMenu();
private:
    Ui::FavoriteWidget*         ui;
    QSqlTableModel*             m_pModel;
    MuiscStyledItemDelegate*    m_pMusicDelegate;
    QMediaPlaylist*             m_pPlayList;
    QMediaPlayer*               m_pMusicPlayer;
    QSqlDatabase                m_pMusicDataBase;
    int                         nCurrentModelRow;
    std::vector<std::string>    m_vMusicLyric;
};

#endif // FAVORITEWIDGET_H
