#-------------------------------------------------
#
# Project created by QtCreator 2016-05-15T18:12:51
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rs16-24
TEMPLATE = app

QMAKE_CXXFLAGS+= -std=c++11 -g
QMAKE_LFLAGS +=  -std=c++11

# =============================================================================
# Boost libs if needed
# =============================================================================
# LIBS += \
#	   -lboost_system\
#	   -lboost_filesystem

# =============================================================================
# Required for flex and bison tools
# =============================================================================
include(moduleParser/flex.pri)
include(moduleParser/bison.pri)
FLEXSOURCES = moduleParser/cppparser/lexer.lex
BISONSOURCES = moduleParser/cppparser/parser.ypp

# =============================================================================
# Math lib <- not really required...but let's be nice
# =============================================================================
LIBS += -lm

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
    moduleLangExporter/langexportertester.cpp \
    classwidget.cpp \
    relationline.cpp \
	moduleCodegen/memberconstructor.cpp \
    moduleParser/parsertester.cpp \
    moduleParser/cppparser/cppparser.cpp \
    moduleParser/cppparser/bisonmessage.cpp \
    relationwidget.cpp \
    moduleCodegen/relationmanager.cpp

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
    moduleLangExporter/langexportertester.hpp \
    classwidget.hpp \
    relationline.hpp \
    moduleCodegen/member.hpp \
	moduleCodegen/memberconstructor.hpp \
    moduleParser/parsertester.hpp \
    moduleParser/cppparser/bisonmessage.hpp \
    moduleParser/cppparser/cppparser.hpp \
    relationwidget.hpp \
    moduleCodegen/relationmanager.hpp

FORMS    += mainwindow.ui

DISTFILES += \
    moduleParser/bison.pri \
    moduleParser/flex.pri
