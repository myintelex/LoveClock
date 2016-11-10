#-------------------------------------------------
#
# Project created by QtCreator 2016-10-26T16:06:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoveClock
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bigmessage.cpp

HEADERS  += mainwindow.h \
    bigmessage.h

FORMS    += mainwindow.ui \
    bigmessage.ui

RESOURCES += \
    image.qrc
RC_FILE += myico.rc
