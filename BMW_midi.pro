#-------------------------------------------------
#
# Project created by QtCreator 2016-02-16T14:15:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "MIDI flashlight"
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        lightsback.cpp \
        lightsfront.cpp \
        about.cpp

QT += serialport
QT += network

HEADERS  += mainwindow.h \
        lightsback.h \
        lightsfront.h \
        about.h

FORMS    += mainwindow.ui \
        about.ui

RESOURCES += \
        images.qrc

RC_FILE = midifalashlight.rc

TRANSLATIONS += midiflashlight_ru.ts
