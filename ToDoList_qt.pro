#-------------------------------------------------
#
# Project created by QtCreator 2015-02-09T21:53:15
#
#-------------------------------------------------

QT       += core gui webkitwidgets

TARGET = ToDoList_qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fileoperator.cpp \
    task.cpp \
    diagramcreator.cpp \
    aboutwindow.cpp \
    settingswindow.cpp

HEADERS  += mainwindow.h \
    fileoperator.h \
    task.h \
    diagramcreator.h \
    defines.h \
    aboutwindow.h \
    settingswindow.h

FORMS    += mainwindow.ui \
    aboutwindow.ui \
    settingswindow.ui

TRANSLATIONS = ToDoList_hu_HU.ts

RESOURCES += \
    todolist.qrc

DISTFILES += \
    about.html
