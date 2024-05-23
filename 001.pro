#-------------------------------------------------
#
# Project created by QtCreator 2015-10-05T20:26:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 001
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    paintwidget.cpp

HEADERS  += mainwindow.h \
    paintwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
