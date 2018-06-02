TEMPLATE = app
CONFIG += console c++11
CONFIG += thread
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    visualisation.cpp \
    wallsegment.cpp \
    wall.cpp \
    cleaner.cpp \
    artist.cpp \
    paintsupply.cpp \
    supplier.cpp

LIBS += -lncurses

HEADERS += \
    visualisation.h \
    wallsegment.h \
    wall.h \
    cleaner.h \
    artist.h \
    colors.h \
    paintcan.h \
    paintsupply.h \
    supplier.h

DISTFILES += \
    map.txt \
    build/map.txt
