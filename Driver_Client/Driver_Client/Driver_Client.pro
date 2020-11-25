#-------------------------------------------------
#
# Project created by QtCreator 2017-05-26T12:57:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Driver_Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client_socket.cpp \
    Driver_Client.cpp \
    tools.cpp \
    login.cpp \
    register.cpp

HEADERS  += mainwindow.h \
    client_exception.h \
    client_socket.h \
    Driver_Client.h \
    network_exception.h \
    tools.h \
    login.h \
    register.h

FORMS    += mainwindow.ui \
    login.ui \
    register.ui
