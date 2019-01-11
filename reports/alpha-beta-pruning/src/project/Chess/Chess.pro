#-------------------------------------------------
#
# Project created by QtCreator 2018-11-19T20:48:59
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamewindow.cpp \
    Chess.cpp

HEADERS  += mainwindow.h \
    gamewindow.h \
    Chess.h

FORMS    += mainwindow.ui \
    gamewindow.ui

DISTFILES += \
    audios/AttackKing.wav \
    audios/back.mp3 \
    audios/Choose.wav \
    audios/Draw.wav \
    audios/Eat.wav \
    audios/Forbid.wav \
    audios/Loss.wav \
    audios/Move.wav \
    audios/NewGame.wav \
    audios/Win.wav

RESOURCES += \
    image.qrc \
    audios.qrc
