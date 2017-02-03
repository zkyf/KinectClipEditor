#-------------------------------------------------
#
# Project created by QtCreator 2017-01-31T18:11:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KinectClipEditor
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


SOURCES += main.cpp\
        mainwindow.cpp \
    viewmodel.cpp \
    qkinectsensor.cpp \
    MatStream.cpp

HEADERS  += mainwindow.h \
    EasyKinect.h \
    KinectOpenCvTools.h \
    MatStream.h \
    viewmodel.h \
    qkinectsensor.h

FORMS    += mainwindow.ui

# Libraries
# OpenCV 3.10
INCLUDEPATH += C:\Libs\OpenCV31\opencv\build\include
LIBS += C:\Libs\OpenCV31\opencv\build\x64\vc12\lib\opencv_world310d.lib

# Kinect SDK 2.0
win32: LIBS += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/Lib/x64/Kinect20.lib"
INCLUDEPATH += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/inc"
DEPENDPATH += "C:/Program Files/Microsoft SDKs/Kinect/v2.0_1409/inc"

# Windows libs
win32:LIBS += -luser32
