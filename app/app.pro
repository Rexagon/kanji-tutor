#-------------------------------------------------
#
# Project created by QtCreator 2017-04-01T19:18:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app

CONFIG += c++14

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR	= ../../bin
OBJECTS_DIR = obj
MOC_DIR = obj

SOURCES += main.cpp\
        mainwindow.cpp \
    kanji.cpp

HEADERS  += mainwindow.h \
    kanji.h

FORMS    += mainwindow.ui
