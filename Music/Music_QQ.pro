#-------------------------------------------------
#
# Project created by QtCreator 2020-10-11T13:36:49
#
#-------------------------------------------------

QT       += core gui widgets multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Music_QQ
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        qmusicwidget.cpp \
    favoritewidget.cpp \
    qrowtableview.cpp \
    muiscstyleditemdelegate.cpp \
    qvolumewgt.cpp

HEADERS += \
        qmusicwidget.h \
    favoritewidget.h \
    qrowtableview.h \
    muiscstyleditemdelegate.h \
    qvolumewgt.h

FORMS += \
        qmusicwidget.ui \
    favoritewidget.ui \
    qvolumewgt.ui

RESOURCES += \
    Resources/images.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Resources/Qss/musicwidget.qss \
    Resources/Qss/favoritewidget.qss \
    Resources/LocalMusic/金玟岐-最初的梦想.mp3 \
    Resources/MusicDataBase/Music_QQ.db \
    Resources/Qss/volumewidget.qss
