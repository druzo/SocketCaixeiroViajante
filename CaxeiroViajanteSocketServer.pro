#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T09:34:03
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CaxeiroViajanteSocketServer
TEMPLATE = app


SOURCES += main.cpp\
        paineldecontrole.cpp \
    serverclient.cpp \
    sockettcpserver.cpp \
    tarefaresultadocaxeiroviajante.cpp \
    tsp.cpp \
    geradorcaminhos.cpp \
    socketclient.cpp

HEADERS  += paineldecontrole.h \
    serverclient.h \
    sockettcpserver.h \
    tarefaresultadocaxeiroviajante.h \
    tsp.h \
    geradorcaminhos.h \
    socketclient.h \
    matriz.h

FORMS    += paineldecontrole.ui
