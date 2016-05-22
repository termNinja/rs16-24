#-------------------------------------------------
#
# Project created by QtCreator 2016-05-15T18:12:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rs16-24
TEMPLATE = app

# Boost libs if needed
# LIBS += \
# 	   -lboost_system\
# 	   -lboost_filesystem

SOURCES += main.cpp\
        mainwindow.cpp \
    moduleCodegen/type.cpp \
    moduleCodegen/variable.cpp \
    moduleCodegen/function.cpp \
	moduleCodegen/codegentester.cpp \
    moduleCodegen/class.cpp \
    moduleCodegen/memberfunction.cpp \
    moduleCodegen/membervariable.cpp \
    moduleLangExporter/langexporter.cpp \
    moduleAppController/resourcemanager.cpp \
    moduleAppController/appcontrollertester.cpp \
    moduleLangExporter/cpplangexporter.cpp \
    moduleLangExporter/langexportertester.cpp

HEADERS  += mainwindow.h \
    moduleCodegen/type.hpp \
    moduleCodegen/variable.hpp \
    moduleCodegen/function.hpp \
	moduleCodegen/codegentester.hpp \
    moduleCodegen/class.hpp \
    moduleCodegen/memberfunction.hpp \
    moduleCodegen/membervariable.hpp \
    moduleLangExporter/langexporter.hpp \
    moduleAppController/resourcemanager.hpp \
    moduleAppController/appcontrollertester.hpp \
    moduleCodegen/membervisibility.hpp \
    moduleLangExporter/cpplangexporter.hpp \
    moduleLangExporter/langexportertester.hpp

FORMS    += mainwindow.ui
