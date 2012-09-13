#-------------------------------------------------
#
# Project created by QtCreator 2012-08-20T20:00:20
#
#-------------------------------------------------

QT       += core\
            gui\
            opengl

TARGET = battleships
TEMPLATE = app


SOURCES += main.cpp \
           engine.cpp \
    ship.cpp \
    point2D.cpp \
    utils.cpp

HEADERS  += engine.h \
    ship.h \
    point2D.h \
    utils.h

LIBS += -lGLU
