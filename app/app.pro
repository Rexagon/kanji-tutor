QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app

CONFIG	+= c++14

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR	= ../../build
OBJECTS_DIR = obj
MOC_DIR = obj

SOURCES += \
    main.cpp \
    window/mainwindow.cpp \
    models/category.cpp \
    models/lesson.cpp \
    models/group.cpp \
    models/hieroglyph.cpp

HEADERS	+= \
    window/mainwindow.h \
    models/category.h \
    models/lesson.h \
    models/group.h \
    models/hieroglyph.h

FORMS	+= window/mainwindow.ui
