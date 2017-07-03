#-------------------------------------------------
#
# Project created by QtCreator 2017-07-03T10:56:37
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled6
TEMPLATE = app
CONFIG += C++14
QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    currency.cpp

HEADERS  += mainwindow.h \
    currency.h

FORMS    += mainwindow.ui
