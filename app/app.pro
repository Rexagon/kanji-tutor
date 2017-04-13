TEMPLATE = app

TARGET	= kanji-tutor
QT      += core gui widgets
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
    models/hieroglyph.cpp \
    widgets/lessonlistitem.cpp \
    widgets/kanjilistitem.cpp \
    widgets/exerciselistitem.cpp \
    window/page.cpp \
    window/pagestart.cpp \
    app.cpp \
    window/pagelesson.cpp \
    window/pagecategory.cpp \
    window/pagecategorykanji.cpp \
    window/pagecategorytests.cpp

HEADERS	+= \
    window/mainwindow.h \
    models/category.h \
    models/lesson.h \
    models/group.h \
    models/hieroglyph.h \
    widgets/lessonlistitem.h \
    widgets/kanjilistitem.h \
    widgets/exerciselistitem.h \
    window/page.h \
    window/pagestart.h \
    app.h \
    window/pagelesson.h \
    window/pagecategory.h \
    window/pagecategorykanji.h \
    window/pagecategorytests.h

FORMS	+= window/mainwindow.ui
