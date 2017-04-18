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
    models/Category.cpp \
    models/Group.cpp \
    models/Hieroglyph.cpp \
    models/Lesson.cpp \
    widgets/ExerciseListItem.cpp \
    widgets/KanjiListItem.cpp \
    widgets/LessonListItem.cpp \
    window/MainWindow.cpp \
    window/Page.cpp \
    window/PageCategory.cpp \
    window/PageCategoryKanji.cpp \
    window/PageCategoryTests.cpp \
    window/PageExercise.cpp \
    window/PageLesson.cpp \
    window/PageStart.cpp \
    App.cpp \
    window/PageResults.cpp

HEADERS	+= \
    window/MainWindow.h \
    window/Page.h \
    window/PageStart.h \
    window/PageLesson.h \
    window/PageCategory.h \
    window/PageCategoryKanji.h \
    window/PageCategoryTests.h \
    window/PageExercise.h \
    models/Category.h \
    models/Group.h \
    models/Hieroglyph.h \
    models/Lesson.h \
    widgets/ExerciseListItem.h \
    widgets/KanjiListItem.h \
    widgets/LessonListItem.h \
    App.h \
    window/PageResults.h

FORMS	+= window/mainwindow.ui

RC_FILE = app.rc
