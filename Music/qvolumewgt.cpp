#include "qvolumewgt.h"
#include "ui_qvolumewgt.h"
#include <QFile>
QVolumeWgt::QVolumeWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QVolumeWgt)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|Qt::Popup);
    this->setFixedSize(40,150);
    InitStyleSheet();
    InitVolumeSolider();
    hide();
    connect(ui->VolumeSlider,SIGNAL(sliderMoved(int)),this,SIGNAL(sgnSliderMoved(int)));
    connect(ui->VolumeSlider,SIGNAL(sliderMoved(int)),this,SLOT(OnSlotChangeVolumeNum(int)));
}

QVolumeWgt::~QVolumeWgt()
{
    delete ui;
}

void QVolumeWgt::mousePressEvent(QMouseEvent *e)
{
    setAttribute(Qt::WA_NoMouseReplay);
    QWidget::mousePressEvent(e);
}

void QVolumeWgt::InitStyleSheet()
{
    QFile qssFile("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/Resources/Qss/volumewidget.qss");//注意qss文件的保存路径
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        QString qssStyle = QLatin1String(qssFile.readAll());
        ui->VolumeSlider->setStyleSheet(qssStyle);
    }
}

void QVolumeWgt::InitVolumeSolider()
{
    ui->VolumeSlider->setValue(99);
}

void QVolumeWgt::OnSlotChangeVolumeNum(int nVolumeNum)
{
    ui->VolumeNum->setText(QString::number(nVolumeNum));
}




