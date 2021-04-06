#ifndef QMUSICANIMATION_H
#define QMUSICANIMATION_H

#include <QWidget>
#include <map>
#include <QLabel>
namespace Ui {
class QMusicAnimation;
}

class QMusicAnimation : public QWidget
{
    Q_OBJECT

public:
    explicit QMusicAnimation(QWidget *parent = nullptr);
    ~QMusicAnimation();

    void InitMusicAnimationStyle();
    void InitMusicLyric(std::string musicstr);
    void ParserLyirs(QString ParStr, std::string musicname);
    void InitLyircLabel(QString musicstr);
    void ChangeLyitcLabel(int posVal);
    void SetCurrentLyric(qint64 position);
signals:
    void sgnCloseMusicLryView(bool);
public slots:
    void OnSlotCloseMusicLryView();
private:
    Ui::QMusicAnimation *ui;
    std::map<std::string, std::map<int,std::string>> m_mLyricName;
    std::map<std::string, QLabel*> m_mLyircLabel;
    QString     m_sCurrentMusicName;
};

#endif // QMUSICANIMATION_H
