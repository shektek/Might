#-------------------------------------------------
#
# Project created by QtCreator 2018-09-08T15:40:04
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtMight
CONFIG   += console
CONFIG   -= app_bundle

QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app
INCLUDEPATH += /usr/include/
LIBS += -L/usr/lib -lncurses

SOURCES += \
    ../../Army.cpp \
    ../../BattleMap.cpp \
    ../../ControlConsole.cpp \
    ../../GameMaster.cpp \
    ../../main.cpp \
    ../../NavigableGrid.cpp \
    ../../Player.cpp \
    ../../Point2D.cpp \
    ../../RenderConsole.cpp \
    ../../Tile.cpp \
    ../../Unit.cpp \
    renderqt.cpp \
    ../../ConsoleHost.cpp

OTHER_FILES += \
    ../../plan.txt \
    ../../makefile

HEADERS += \
    ../../Army.h \
    ../../ArrangementStrategy.h \
    ../../BattleMap.h \
    ../../ControlConsole.h \
    ../../GameMaster.h \
    ../../NavigableGrid.h \
    ../../Player.h \
    ../../Point2D.h \
    ../../RenderConsole.h \
    ../../RenderConsoleColours.h \
    ../../Tile.h \
    ../../Unit.h \
    ../../OrdinalPosition.h \
    renderqt.h \
    ../../AppHost.h \
    ../../ConsoleHost.h

FORMS += \
    renderqt.ui
