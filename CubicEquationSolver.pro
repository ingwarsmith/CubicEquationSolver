#-------------------------------------------------
#
# Project created by QtCreator 2015-04-15T15:27:30
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CubicEquationSolver
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cubicequationcardano.cpp

HEADERS  += mainwindow.h \
    cubicequationcardano.h

FORMS    += mainwindow.ui
