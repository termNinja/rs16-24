#-------------------------------------------------
#
# Project created by QtCreator 2016-05-15T18:12:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rs16-24
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    moduleCodegen/type.cpp \
    moduleCodegen/variable.cpp \
    moduleCodegen/function.cpp

HEADERS  += mainwindow.h \
    moduleCodegen/type.hpp \
    moduleCodegen/variable.hpp \
    moduleCodegen/function.hpp

FORMS    += mainwindow.ui
