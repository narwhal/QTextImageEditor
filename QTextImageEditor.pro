#-------------------------------------------------
#
# Project created by QtCreator 2015-03-21T10:35:21
#
#-------------------------------------------------

QT       += core gui widgets

include(QTextImage/qtextimage.pri)
TARGET = qtieditor
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    penmodel.cpp

HEADERS  += mainwindow.h \
    penmodel.h

FORMS    += mainwindow.ui