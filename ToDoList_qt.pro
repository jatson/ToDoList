#-------------------------------------------------
#
# Project created by QtCreator 2015-02-09T21:53:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToDoList_qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fileoperator.cpp \
    task.cpp \
    diagramcreator.cpp \
    aboutwindow.cpp

HEADERS  += mainwindow.h \
    fileoperator.h \
    task.h \
    diagramcreator.h \
    defines.h \
    aboutwindow.h

FORMS    += mainwindow.ui \
    aboutwindow.ui

TRANSLATIONS = ToDoList_hu_HU.ts
