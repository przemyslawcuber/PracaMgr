#-------------------------------------------------
#
# Project created by QtCreator 2015-05-17T14:05:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PracaMgr
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    readpcapfile.cpp \
    kmean.cpp \
    packet.cpp \
    preparedata.cpp \
    conversationgroup.cpp \
    sourceipbehavior.cpp

HEADERS  += mainwindow.h \
    readpcapfile.h \
    kmean.h \
    packet.h \
    preparedata.h \
    conversationgroup.h \
    sourceipbehavior.h

FORMS    += mainwindow.ui

linux-g++ { # For Linux
    LIBS += \
       -lpcap\
       -lboost_system\
}

DISTFILES += \
    README.md
