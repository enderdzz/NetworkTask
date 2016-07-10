#-------------------------------------------------
#
# Project created by QtCreator 2016-06-22T16:34:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = netsim_ui
TEMPLATE = app


SOURCES += main.cpp\
        netsim_mainwindow.cpp \
    statuswidget.cpp \
    dlgabout.cpp \
    simsender.cpp \
    simreceiver.cpp \
    graphwidget.cpp

HEADERS  += netsim_mainwindow.h \
    including.h \
    statuswidget.h \
    dlgabout.h \
    simsender.h \
    simreceiver.h \
    graphwidget.h

FORMS    += netsim_mainwindow.ui \
    statuswidget.ui \
    dlgabout.ui
