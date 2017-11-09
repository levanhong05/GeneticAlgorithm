#-------------------------------------------------
#
# Project created by QtCreator 2017-11-09T10:18:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix:TARGET = ../../bin/GeneticAlgorithm
win32:TARGET = ../../../dist/bin/GeneticAlgorithm

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
            main.cpp \
            aboutscreen.cpp \
            gaapplication.cpp \
    application.cpp

HEADERS += \
            aboutscreen.h \
            gaapplication.h \
    application.h

FORMS += \
            aboutscreen.ui \
            gaapplication.ui


win32:LIBS += -L$$OUT_PWD/../../dist/bin/ -llogger
unix:LIBS += -L$$OUT_PWD/../../modules/logger/ -llogger

INCLUDEPATH += $$PWD/../../modules/logger
DEPENDPATH += $$PWD/../../modules/logger

unix:LIBS += -L$$OUT_PWD/../../modules/console -lconsole
win32:LIBS += -L$$OUT_PWD/../../dist/bin -lconsole

INCLUDEPATH += $$PWD/../../modules/console
DEPENDPATH += $$PWD/../../modules/console

win32:RC_FILE = gaapplication.rc

RESOURCES += \
    gaa_res.qrc

