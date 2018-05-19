TEMPLATE = app
CONFIG += console c++11
CONFIG += thread
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    visualisation.cpp \
    fork.cpp \
    wallsegment.cpp \
    wall.cpp \
    cleaner.cpp \
    artist.cpp

LIBS += -lncurses

HEADERS += \
    visualisation.h \
    fork.h \
    wallsegment.h \
    wall.h \
    cleaner.h \
    artist.h \
    colors.h
