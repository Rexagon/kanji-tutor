QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app

CONFIG	+= c++14

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR	= ../../bin
OBJECTS_DIR = obj
MOC_DIR = obj

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    kanji.cpp \
    category.cpp \
    lesson.cpp \
    group.cpp

HEADERS	+= \
    mainwindow.h \
    kanji.h \
    category.h \
    lesson.h \
    group.h

FORMS	+= mainwindow.ui
