#-------------------------------------------------
#
# Project created by QtCreator 2016-10-03T15:24:41
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gobang3
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Game.cpp \
    ChessPlay.cpp

HEADERS  += MainWindow.h \
    Game.h \
    ChessPlay.h

FORMS    += MainWindow.ui \
    ChessPlay.ui

RESOURCES += \
    resource.qrc
