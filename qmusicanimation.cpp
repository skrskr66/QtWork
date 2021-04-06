#include "qmusicanimation.h"
#include "ui_qmusicanimation.h"
#include <QPropertyAnimation>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <map>
#include <QLabel>
#include <QVBoxLayout>
QMusicAnimation::QMusicAnimation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMusicAnimation)
{
    ui->setupUi(this);
    InitMusicAnimationStyle();
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(OnSlotCloseMusicLryView()));
}

QMusicAnimation::~QMusicAnimation()
{
    delete ui;
}

void QMusicAnimation::InitMusicAnimationStyle()
{
    QFile qssFile("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/Resources/Qss/musicanimation.qss");//注意qss文件的保存路径
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        QString qssStyle = QLatin1String(qssFile.readAll());
        this->setStyleSheet(qssStyle);
    }
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void QMusicAnimation::InitMusicLyric(std::string musicstr)
{
    QFile qssFile("/Users/liuyucheng/WorkSpace/Qt/Music_QQ/Resources/Lyric/" + QString::fromStdString(musicstr) + ".Lrc");//注意qss文件的保存路径
    qDebug()<<"/Users/liuyucheng/WorkSpace/Qt/Music_QQ/Resources/Lyric/" + QString::fromStdString(musicstr)<<endl;
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        QString qssStyle = QString::fromUtf8(qssFile.readAll());
        ParserLyirs(qssStyle, musicstr);
        qDebug()<<qssStyle<<endl;
    }
}

void QMusicAnimation::ParserLyirs(QString ParStr, std::string musicname)
{
    QString playstr = ParStr;
    if(playstr != "")
    {
       QStringList s1 = playstr.split("\n");
       for(int i = 0;i < s1.size(); ++i)
       {
            QString s2 = s1.at(i);
            QRegExp ipRegExp = QRegExp("\\[\\d\\d\\S\\d\\d\\]");
            //若包含则返回flase
            bool match = ipRegExp.indexIn(s2);
            if (match == false)
            {
                //时间解析格式(分*60+秒)*100
                int s_1 = s2.mid(1, 2).toInt();      //分
                int s_2 = s2.mid(4, 2).toInt();      //秒
                //int s_3 = s2.mid(7, 2).toInt();      //厘秒
                int s_count = (s_1 * 60 + s_2) * 100; //+ s_3;
                int lrctime = s_count;
                QString lrcstr = s2.mid(7);
                qDebug()<<"lrctime = "<<lrctime<< "- - -" <<"lrcstr = "<<lrcstr<<endl;
                m_mLyricName[musicname].insert(std::map<int,std::string>::value_type(lrctime,lrcstr.toStdString()));
            }
       }
    }
}

void QMusicAnimation::InitLyircLabel(QString musicstr)
{
    m_sCurrentMusicName = musicstr;
    std::map<std::string, std::map<int,std::string>>::iterator mp1;
    QVBoxLayout* verticalLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    for(mp1 = m_mLyricName.begin();mp1 != m_mLyricName.end();mp1++)
    {
        std::map<int,std::string>::iterator mp2 = mp1->second.begin();
        while(mp2 != mp1->second.end())
        {
            QLabel* lab = new QLabel(ui->scrollAreaWidgetContents);
            verticalLayout->addWidget(lab);
            lab->setText(QString::fromStdString(mp2->second));
            m_mLyircLabel[mp2->second] = lab;
            mp2++;
        }
    }
}

void QMusicAnimation::ChangeLyitcLabel(int posVal)
{
    std::map<int,std::string>::iterator mp = m_mLyricName[m_sCurrentMusicName.toStdString()].begin();
    while(mp != m_mLyricName[m_sCurrentMusicName.toStdString()].end())
    {
        QPalette pe;
        pe.setColor(QPalette::WindowText,Qt::black);
        m_mLyircLabel[mp->second]->setPalette(pe);
        mp++;
    }
}

void QMusicAnimation::SetCurrentLyric(qint64 position)
{
    qint64 pos = position / 10;
    std::map<int,std::string>::iterator mp = m_mLyricName[m_sCurrentMusicName.toStdString()].begin();
    while(mp != m_mLyricName[m_sCurrentMusicName.toStdString()].end())
    {
        if(pos-50 <= mp->first && pos + 50 >= mp->first)
        {
            QPalette pe;
            pe.setColor(QPalette::WindowText,"#2eb372");
            m_mLyircLabel[mp->second]->setPalette(pe);
            if(mp != m_mLyricName[m_sCurrentMusicName.toStdString()].begin())
            {
                mp--;
            }
            if(mp != m_mLyricName[m_sCurrentMusicName.toStdString()].end())
            {
                QPalette pe;
                pe.setColor(QPalette::WindowText,Qt::black);
                m_mLyircLabel[mp->second]->setPalette(pe);
            }
            mp = m_mLyricName[m_sCurrentMusicName.toStdString()].end();
            break;
        }
        mp++;
    }
}

void QMusicAnimation::OnSlotCloseMusicLryView()
{
    emit sgnCloseMusicLryView(false);
}



