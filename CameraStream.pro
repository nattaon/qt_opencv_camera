QT += core
QT -= gui

CONFIG += c++11

TARGET = CameraStream
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    imgproc.cpp \
    webcam.cpp

HEADERS += \
    imgproc.h \
    webcam.h
