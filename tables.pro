#-------------------------------------------------
#
# Project created by QtCreator 2014-10-16T19:28:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -Wno-unused-parameter

TARGET = tables
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablerowmodel.cpp \
    ordereditemsdialog.cpp

HEADERS  += mainwindow.h \
    tablerowmodel.h \
    ordereditemsdialog.h

FORMS    += mainwindow.ui \
    ordereditemsdialog.ui
