#include "favoritewidget.h"
#include "ui_favoritewidget.h"
#include <QWidget>
#include <QFile>
#include <QDir>
#include <QFont>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QToolTip>
#include <QStyledItemDelegate>
#include <QTableView>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlRecord>
#include "muiscstyleditemdelegate.h"
#include "globaldefine.h"
#include <QString>
#include <string>
#include <QMenu>
#include <QCursor>
FavoriteWidget::FavoriteWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FavoriteWidget),
    nCurrentModelRow(-1)
{
    ui->setupUi(this);
    setMouseTracking(true);
    InitInterface();
    InitStackedWidget();
    InitTableWidget();
    InitMusicList();
    InitDataBase();
    connect(ui->musicpushButton,SIGNAL(clicked()),this,SLOT(onSlotClickChangeTable()));
    connect(ui->albumpushButton,SIGNAL(clicked()),this,SLOT(onSlotClickChangeTable()));
    connect(ui->listpushButton,SIGNAL(clicked()),this,SLOT(onSlotClickChangeTable()));
    connect(ui->mvpushButton,SIGNAL(clicked()),this,SLOT(onSlotClickChangeTable()));
    connect(ui->musictableWidget, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(onSlotTableClicked(const QModelIndex&)));
    connect(m_pMusicPlayer,SIGNAL(positionChanged(qint64)),this,SIGNAL(sgnPositionChanged(qint64)));
    connect(m_pMusicPlayer,SIGNAL(durationChanged(qint64)),this,SIGNAL(sgnDurationChanged(qint64)));
    connect(ui->musictableWidget,SIGNAL(sgnRClickMenu()),this,SLOT(OnSlotRClickMenu()));
}

FavoriteWidget::~FavoriteWidget()
{
    delete ui;
}

void FavoriteWidget::InitInterface()
{
    QFont ft;
    ft.setPointSize(32);
    ui->label_6->setFont(ft);
    QFile qssFile("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/Resources/Qss/favoritewidget.qss");//注意qss文件的保存路径
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        QString qssStyle = QLatin1String(qssFile.readAll());
        ui->musicpushButton->setStyleSheet(qssStyle);
        ui->albumpushButton->setStyleSheet(qssStyle);
        ui->listpushButton->setStyleSheet(qssStyle);
        ui->mvpushButton->setStyleSheet(qssStyle);
        ui->label_6->setStyleSheet(qssStyle);
        ui->PlaypushButton->setStyleSheet(qssStyle);
        ui->DownloadpushButton->setStyleSheet(qssStyle);
        ui->MultipushButton->setStyleSheet(qssStyle);
        ui->lineEdit->setStyleSheet(qssStyle);
        ui->musictableWidget->setStyleSheet(qssStyle);
    }
    ui->musicpushButton->setChecked(true);
    ui->albumpushButton->setChecked(false);
    ui->listpushButton->setChecked(false);
    ui->mvpushButton->setChecked(false);
}

void FavoriteWidget::InitStackedWidget()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void FavoriteWidget::InitTableWidget()
{
    m_pMusicDelegate = new MuiscStyledItemDelegate();
    ui->musictableWidget->setItemDelegate(m_pMusicDelegate);
    ui->musictableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    ui->musictableWidget->verticalHeader()->setDefaultSectionSize(50);

    ui->musictableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);//表头不可拖动
    ui->musictableWidget->verticalHeader()->setVisible(false);//列表头不可见
    ui->musictableWidget->setShowGrid(false);
    ui->musictableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->musictableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->musictableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->musictableWidget->setMouseTracking(true);
}

void FavoriteWidget::InitMusicList()
{
    m_pMusicPlayer = new QMediaPlayer(this);
    m_pPlayList = new QMediaPlaylist(this);
    m_pPlayList->setPlaybackMode(QMediaPlaylist::Loop);
}

void FavoriteWidget::InitDataBase()
{
    m_pMusicDataBase = QSqlDatabase::addDatabase("QSQLITE","Localhost");
    m_pMusicDataBase.setHostName("Localhost");
    m_pMusicDataBase.setPort(3306);
    //setDatabaseName填写的是db文件的路径！！！大坑！！！
    m_pMusicDataBase.setDatabaseName("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/Resources/MusicDataBase/Music_QQ.db");
    m_pMusicDataBase.setUserName("root");
    m_pMusicDataBase.setPassword("123456");
    if(!m_pMusicDataBase.open())
    {
         qDebug()<<"Open DataBase Failed!"<<endl;
         return;
    }
    else
    {
        qDebug()<<"Open DataBase Success!"<<endl;
    }

    m_pMusicDataBase = QSqlDatabase::database("Localhost"); //建立数据库连接
    QSqlQuery m_pMusicQuery(m_pMusicDataBase);

    m_pModel = new QSqlTableModel(this, m_pMusicDataBase);
    m_pModel->setTable("Favoritemusic");//输入表名
    m_pModel->select();//选择全表
    HandleMusicTable();

    ui->musictableWidget->setModel(m_pModel);
    ui->musictableWidget->setColumnWidth(0,370);//设置每列的宽,tableview改变列宽必须放在this->model后面
    ui->musictableWidget->setColumnWidth(1,230);
    ui->musictableWidget->setColumnWidth(2,190);
    ui->musictableWidget->setColumnWidth(3,160);
    ui->musictableWidget->setColumnWidth(4,0);
    //m_pMusicQuery.exec("insert into Favoritemusic values('最初的梦想','金玟岐','歌曲合辑','02:49',1)");
}

void FavoriteWidget::HandleMusicTable()
{
    for(int i = 0; i < m_pModel->rowCount(); ++i)
    {
        QString MusicName = m_pModel->record(i).value("歌曲").toString();
        if(m_pModel->record(i).value("歌词").toInt())
        {
            m_vMusicLyric.push_back(MusicName.toStdString());
        }
        QString personName = m_pModel->record(i).value("歌手").toString();
        QString strLocalFile = LOCALMUSICPATH + personName + "-" + MusicName + ".mp3";
        qDebug()<<strLocalFile<<endl;

        m_pPlayList->addMedia(QUrl::fromLocalFile(strLocalFile));

        QString Tmpstr = tr("歌曲%1").arg(m_pPlayList->mediaCount());
        ui->musicpushButton->setText(Tmpstr);
    }
    m_pMusicPlayer->setMedia(m_pPlayList);
}

void FavoriteWidget::PauseOrPlayMusic()
{
    if(m_pMusicPlayer->state() == QMediaPlayer::PlayingState)//判断音乐是否播放状态，不用isaudioavaliable
    {
        m_pMusicPlayer->pause();
    }
    else
    {
        m_pMusicPlayer->play();
    }
}

void FavoriteWidget::PlaypPreviousMusic()
{
    if(m_pMusicPlayer->state() == QMediaPlayer::PlayingState)//判断音乐是否播放状态，不用isaudioavaliable
    {
        if(m_pPlayList->currentIndex() == 0)
        {
            m_pPlayList->setCurrentIndex(m_pModel->rowCount() - 1);
            m_pMusicPlayer->play();
        }
        else
        {
            m_pPlayList->setCurrentIndex(m_pPlayList->currentIndex() - 1);
            m_pMusicPlayer->play();
        }
    }
}

void FavoriteWidget::PlayNextMusic()
{
    //切换音乐
    if(m_pMusicPlayer->state() == QMediaPlayer::PlayingState)//判断音乐是否播放状态，不用isaudioavaliable
    {
        if(m_pPlayList->currentIndex() == m_pModel->rowCount() - 1)
        {
            m_pPlayList->setCurrentIndex(0);
            m_pMusicPlayer->play();
        }
        else
        {
            m_pPlayList->setCurrentIndex(m_pPlayList->currentIndex() + 1);
            m_pMusicPlayer->play();
        }
    }
    //切换列表选中状态
    ui->musictableWidget->selectRow(m_pPlayList->currentIndex());
}

void FavoriteWidget::Do(QAction *ActionVal)
{
    if(nullptr == ActionVal)
    {
        return;
    }

    switch (ActionVal->data().toInt())
    {
    case RClickVal::NEXT_MUSIC:
    {
        PlayNextMusic();
        break;
    }
    case RClickVal::PLAY_MUSIC:
    {
        break;
    }
    default:
        break;
    }
}

void FavoriteWidget::onSlotClickChangeTable()
{
    QPushButton* GetBtnType = qobject_cast<QPushButton*>(sender());
    if(GetBtnType == ui->musicpushButton)
    {
        ui->musicpushButton->setChecked(true);
        ui->albumpushButton->setChecked(false);
        ui->listpushButton->setChecked(false);
        ui->mvpushButton->setChecked(false);
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(GetBtnType == ui->albumpushButton)
    {
        ui->musicpushButton->setChecked(false);
        ui->albumpushButton->setChecked(true);
        ui->listpushButton->setChecked(false);
        ui->mvpushButton->setChecked(false);
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if(GetBtnType == ui->listpushButton)
    {
        ui->musicpushButton->setChecked(false);
        ui->albumpushButton->setChecked(false);
        ui->listpushButton->setChecked(true);
        ui->mvpushButton->setChecked(false);
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if(GetBtnType == ui->mvpushButton)
    {
        ui->musicpushButton->setChecked(false);
        ui->albumpushButton->setChecked(false);
        ui->listpushButton->setChecked(false);
        ui->mvpushButton->setChecked(true);
        ui->stackedWidget->setCurrentIndex(3);
    }
}

void FavoriteWidget::onSlotTableClicked(const QModelIndex& index)
{
    m_pMusicPlayer->stop();
    m_pPlayList->setCurrentIndex(index.row());
    qDebug()<<index.data().toString()<<endl;
    m_pMusicPlayer->play();
    emit sgnCurrentplaybutton(BUTTON_CURRENT_PLAY, index.data().toString());
}

void FavoriteWidget::OnSlotColtrolvolume(int nValue)
{
    m_pMusicPlayer->setVolume(nValue);
}

void FavoriteWidget::OnSlotSwitchPosition(int posVal)
{
    m_pMusicPlayer->setPosition(posVal);
    emit sgnMusicViewChanged(posVal);
}

void FavoriteWidget::OnSlotPlayNextMusic()
{
    PlayNextMusic();
}

void FavoriteWidget::OnSlotRClickMenu()
{
    QMenu* MusicMenu = new QMenu(ui->musictableWidget);

    //播放
    QAction* PlayMusic = new QAction(ui->musictableWidget);
    PlayMusic->setData(RClickVal::PLAY_MUSIC);
    PlayMusic->setText(QString::fromLocal8Bit("播放"));
    MusicMenu->addAction(PlayMusic);

    //下一首歌曲
    QAction* NextMusic = new QAction(ui->musictableWidget);
    NextMusic->setData(RClickVal::NEXT_MUSIC);
    NextMusic->setText(QString::fromLocal8Bit("下一首"));
    MusicMenu->addAction(NextMusic);

    MusicMenu->addSeparator();

    //下载
    QAction* DownLoadMusic = new QAction(ui->musictableWidget);
    DownLoadMusic->setData(RClickVal::DOWNLOAD_MUSIC);
    DownLoadMusic->setText(QString::fromLocal8Bit("下载"));
    MusicMenu->addAction(DownLoadMusic);

    MusicMenu->addSeparator();

    //删除
    QAction* DeleteMusic = new QAction(ui->musictableWidget);
    DeleteMusic->setData(RClickVal::DELETE_MUSIC);
    DeleteMusic->setText(QString::fromLocal8Bit("删除"));
    MusicMenu->addAction(DeleteMusic);

    QAction* val = MusicMenu->exec(QCursor::pos());
    qDebug()<<val<<endl;
    Do(val);
}


