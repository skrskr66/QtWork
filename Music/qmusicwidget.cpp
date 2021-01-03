#include "qmusicwidget.h"
#include "ui_qmusicwidget.h"
#include <QWidget>
#include <QFile>
#include <QDir>
#include <QDebug>
#include "qvolumewgt.h"
QMusicWidget::QMusicWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMusicWidget),
    m_nIsPlaySta(0)
{
    ui->setupUi(this);

    InitInterface();
    InitButton();
    InitStackedWidget();
    InitSlider();
    connect(ui->MusicLibPushButton,SIGNAL(clicked()),this,SLOT(OnSlotClickChangeTable()));
    connect(ui->VideoPushButton,SIGNAL(clicked()),this,SLOT(OnSlotClickChangeTable()));
    connect(ui->RadioPushButton,SIGNAL(clicked()),this,SLOT(OnSlotClickChangeTable()));
    connect(ui->MyfavoritePushButton,SIGNAL(clicked()),this,SLOT(OnSlotClickChangeTable()));
    connect(ui->LocalMusicPushButton,SIGNAL(clicked()),this,SLOT(OnSlotClickChangeTable()));
    connect(ui->DownloadMusicPushButton,SIGNAL(clicked()),this,SLOT(OnSlotClickChangeTable()));
    connect(ui->HistoryPushButton,SIGNAL(clicked()),this,SLOT(OnSlotClickChangeTable()));
    connect(ui->PurchasePushButton,SIGNAL(clicked()),this,SLOT(OnSlotClickChangeTable()));
    connect(ui->favwidget,SIGNAL(sgnPositionChanged(qint64)),this,SLOT(OnSlotUpdatePosition(qint64)));
    connect(ui->favwidget,SIGNAL(sgnDurationChanged(qint64)),this,SLOT(OnSlotDurationChanged(qint64)));
    connect(ui->favwidget,SIGNAL(sgnCurrentplaybutton(int)),this,SLOT(OnSlotCurrentButton(int)));
    connect(ui->PlayButton,SIGNAL(clicked()),this,SLOT(OnSlotPlayOrPauseMusic()));
    connect(ui->VolumeButton,SIGNAL(clicked()),this,SLOT(OnSlotChangeVolume()));
    connect(VolumeWidget,SIGNAL(sgnSliderMoved(int)),ui->favwidget,SLOT(OnSlotColtrolvolume(int)));
}

QMusicWidget::~QMusicWidget()
{
    delete ui;
}

void QMusicWidget::InitInterface()
{
    MainWidget = ui->MainWidget;
    MainWidget->setGeometry(210,0,991,701);
    MainWidget->setStyleSheet("background-color:#F6F6F6;");

    SubWidget = ui->SubWidget;
    SubWidget->setGeometry(0,0,211,701);
    SubWidget->setStyleSheet("background-color:#F0F0F0;");

    VolumeWidget = new QVolumeWgt(this);
}

void QMusicWidget::InitButton()
{
    QFile qssFile("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/Resources/Qss/musicwidget.qss");//注意qss文件的保存路径
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        QString qssStyle = QLatin1String(qssFile.readAll());
        ui->MusicLibPushButton->setStyleSheet(qssStyle);
        ui->VideoPushButton->setStyleSheet(qssStyle);
        ui->RadioPushButton->setStyleSheet(qssStyle);
        ui->MyfavoritePushButton->setStyleSheet(qssStyle);
        ui->LocalMusicPushButton->setStyleSheet(qssStyle);
        ui->DownloadMusicPushButton->setStyleSheet(qssStyle);
        ui->HistoryPushButton->setStyleSheet(qssStyle);
        ui->PurchasePushButton->setStyleSheet(qssStyle);

        //控制播放
        ui->PlayButton->setStyleSheet(qssStyle);
        ui->NextButton->setStyleSheet(qssStyle);
        ui->previousButton->setStyleSheet(qssStyle);

        //音量键
        ui->VolumeButton->setStyleSheet(qssStyle);
    }

    ui->MusicLibPushButton->setChecked(true);
    ui->VideoPushButton->setChecked(false);
    ui->RadioPushButton->setChecked(false);
    ui->MyfavoritePushButton->setChecked(false);
    ui->LocalMusicPushButton->setChecked(false);
    ui->DownloadMusicPushButton->setChecked(false);
    ui->HistoryPushButton->setChecked(false);
    ui->PurchasePushButton->setChecked(false);

    ui->MusicLibPushButton->setFixedSize(163,28);
    ui->MusicLibPushButton->setIcon(QIcon(QPixmap("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/image/音乐库icon.png")));
    ui->MusicLibPushButton->setIconSize(QSize(16,16));
    ui->VideoPushButton->setFixedSize(163,28);
    ui->VideoPushButton->setIcon(QIcon(QPixmap("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/image/视频icon.png")));
    ui->VideoPushButton->setIconSize(QSize(20,20));
    ui->RadioPushButton->setFixedSize(163,28);
    ui->RadioPushButton->setIcon(QIcon(QPixmap("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/image/电台icon.png")));
    ui->RadioPushButton->setIconSize(QSize(20,20));
    ui->MyfavoritePushButton->setFixedSize(163,28);
    ui->MyfavoritePushButton->setIcon(QIcon(QPixmap("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/image/我喜欢icon.png")));
    ui->MyfavoritePushButton->setIconSize(QSize(16,16));
    ui->LocalMusicPushButton->setFixedSize(163,28);
    ui->LocalMusicPushButton->setIcon(QIcon(QPixmap("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/image/本地歌曲icon.png")));
    ui->LocalMusicPushButton->setIconSize(QSize(16,16));
    ui->DownloadMusicPushButton->setFixedSize(163,28);
    ui->DownloadMusicPushButton->setIcon(QIcon(QPixmap("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/image/下载icon.png")));
    ui->DownloadMusicPushButton->setIconSize(QSize(16,16));
    ui->HistoryPushButton->setFixedSize(163,28);
    ui->HistoryPushButton->setIcon(QIcon(QPixmap("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/image/播放历史icon.png")));
    ui->HistoryPushButton->setIconSize(QSize(16,16));
    ui->PurchasePushButton->setFixedSize(163,28);
    ui->PurchasePushButton->setIcon(QIcon(QPixmap("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/image/已购音乐icon.png")));
    ui->PurchasePushButton->setIconSize(QSize(16,16));

    ui->PlayButton->setChecked(false);
}

void QMusicWidget::InitStackedWidget()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void QMusicWidget::InitSlider()
{
    QFile qssFile("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/Resources/Qss/musicwidget.qss");//注意qss文件的保存路径
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        QString qssStyle = QLatin1String(qssFile.readAll());
        ui->playSlider->setStyleSheet(qssStyle);
    }
}

void QMusicWidget::OnSlotClickChangeTable()
{
    QPushButton* GetBtnType = qobject_cast<QPushButton*>(sender());
    if(GetBtnType == ui->MusicLibPushButton)
    {
        ui->MusicLibPushButton->setChecked(true);
        ui->VideoPushButton->setChecked(false);
        ui->RadioPushButton->setChecked(false);
        ui->LocalMusicPushButton->setChecked(false);
        ui->MyfavoritePushButton->setChecked(false);
        ui->DownloadMusicPushButton->setChecked(false);
        ui->HistoryPushButton->setChecked(false);
        ui->PurchasePushButton->setChecked(false);
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(GetBtnType == ui->VideoPushButton)
    {
        ui->MusicLibPushButton->setChecked(false);
        ui->VideoPushButton->setChecked(true);
        ui->RadioPushButton->setChecked(false);
        ui->LocalMusicPushButton->setChecked(false);
        ui->MyfavoritePushButton->setChecked(false);
        ui->DownloadMusicPushButton->setChecked(false);
        ui->HistoryPushButton->setChecked(false);
        ui->PurchasePushButton->setChecked(false);
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if(GetBtnType == ui->RadioPushButton)
    {
        ui->MusicLibPushButton->setChecked(false);
        ui->VideoPushButton->setChecked(false);
        ui->RadioPushButton->setChecked(true);
        ui->LocalMusicPushButton->setChecked(false);
        ui->MyfavoritePushButton->setChecked(false);
        ui->DownloadMusicPushButton->setChecked(false);
        ui->HistoryPushButton->setChecked(false);
        ui->PurchasePushButton->setChecked(false);
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if(GetBtnType == ui->LocalMusicPushButton)
    {
        ui->MusicLibPushButton->setChecked(false);
        ui->VideoPushButton->setChecked(false);
        ui->RadioPushButton->setChecked(false);
        ui->LocalMusicPushButton->setChecked(true);
        ui->MyfavoritePushButton->setChecked(false);
        ui->DownloadMusicPushButton->setChecked(false);
        ui->HistoryPushButton->setChecked(false);
        ui->PurchasePushButton->setChecked(false);
        ui->stackedWidget->setCurrentIndex(4);
    }
    else if(GetBtnType == ui->MyfavoritePushButton)
    {
        ui->MusicLibPushButton->setChecked(false);
        ui->VideoPushButton->setChecked(false);
        ui->RadioPushButton->setChecked(false);
        ui->LocalMusicPushButton->setChecked(false);
        ui->MyfavoritePushButton->setChecked(true);
        ui->DownloadMusicPushButton->setChecked(false);
        ui->HistoryPushButton->setChecked(false);
        ui->PurchasePushButton->setChecked(false);
        ui->stackedWidget->setCurrentIndex(3);
    }
    else if(GetBtnType == ui->DownloadMusicPushButton)
    {
        ui->MusicLibPushButton->setChecked(false);
        ui->VideoPushButton->setChecked(false);
        ui->RadioPushButton->setChecked(false);
        ui->LocalMusicPushButton->setChecked(false);
        ui->MyfavoritePushButton->setChecked(false);
        ui->DownloadMusicPushButton->setChecked(true);
        ui->HistoryPushButton->setChecked(false);
        ui->PurchasePushButton->setChecked(false);
        ui->stackedWidget->setCurrentIndex(5);
    }
    else if(GetBtnType == ui->HistoryPushButton)
    {
        ui->MusicLibPushButton->setChecked(false);
        ui->VideoPushButton->setChecked(false);
        ui->RadioPushButton->setChecked(false);
        ui->LocalMusicPushButton->setChecked(false);
        ui->MyfavoritePushButton->setChecked(false);
        ui->DownloadMusicPushButton->setChecked(false);
        ui->HistoryPushButton->setChecked(true);
        ui->PurchasePushButton->setChecked(false);
        ui->stackedWidget->setCurrentIndex(6);
    }
    else if(GetBtnType == ui->PurchasePushButton)
    {
        ui->MusicLibPushButton->setChecked(false);
        ui->VideoPushButton->setChecked(false);
        ui->RadioPushButton->setChecked(false);
        ui->LocalMusicPushButton->setChecked(false);
        ui->MyfavoritePushButton->setChecked(false);
        ui->DownloadMusicPushButton->setChecked(false);
        ui->HistoryPushButton->setChecked(false);
        ui->PurchasePushButton->setChecked(true);
        ui->stackedWidget->setCurrentIndex(7);
    }
}

void QMusicWidget::OnSlotUpdatePosition(qint64 position)
{
    ui->playSlider->setValue(position);
}

void QMusicWidget::OnSlotDurationChanged(qint64 position)
{
    ui->playSlider->setRange(0, position);//根据播放时长来设置滑块的范围
    ui->playSlider->setEnabled(position > 0);
    ui->playSlider->setPageStep(position / 10);//以及每一步的步数
}

void QMusicWidget::OnSlotCurrentButton(int nStatus)
{
    //播放按钮状态为1
    m_nIsPlaySta = nStatus;
    if(nStatus)
    {
        ui->PlayButton->setChecked(true);
    }
}

void QMusicWidget::OnSlotPlayOrPauseMusic()
{
    if(m_nIsPlaySta)
    {
        ui->favwidget->PauseOrPlayMusic();
    }
}

void QMusicWidget::OnSlotChangeVolume()
{
    if(VolumeWidget->isHidden())
    {
        QPoint moveTo = ui->VolumeButton->mapToGlobal(QPoint(0,0));//将绝对位置对应到控件的相对位置
        VolumeWidget->setGeometry(moveTo.x()-10,moveTo.y()-160,40,150);
        VolumeWidget->show();
    }
    else
    {
        VolumeWidget->hide();
    }
}
