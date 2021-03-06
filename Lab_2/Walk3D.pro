#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T13:46:25
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lopengl32

TARGET = Walk3D
TEMPLATE = app


SOURCES += main.cpp \
    ui/window3d.cpp \
    nodes/coloredcube.cpp \
    gl/scenenode.cpp \
    gl/basescene.cpp \
    gameapplication.cpp \
    gl/scenecamera.cpp \
    gl/glhelper.cpp \
    ui/imovecontroller.cpp \
    ui/freemovecontroller.cpp \
    ui/rotatemovecontroller.cpp

HEADERS  += \
    ui/window3d.h \
    gl/scenenode.h \
    nodes/coloredcube.h \
    gl/basescene.h \
    gameapplication.h \
    gl/iscenecamera.h \
    gl/scenecamera.h \
    gl/glhelper.h \
    ui/imovecontroller.h \
    ui/freemovecontroller.h \
    ui/rotatemovecontroller.h

FORMS    +=
