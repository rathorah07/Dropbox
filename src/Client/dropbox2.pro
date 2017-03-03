#-------------------------------------------------
#
# Project created by QtCreator 2015-02-20T22:23:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lcrypto -lssl -lsqlite3
CONFIG += c++11 warn_off
OBJECTS_DIR = ./obj
INCLUDEPATH = ./include

UI_DIR = ./intermediate
MOC_DIR = ./intermediate
RCC_DIR = ./intermediate
TARGET = dropbox2
TEMPLATE = app


SOURCES += \
    src/dropbox2.cpp \
    src/filehandle.cpp \
    src/fileinfo1.cpp \
    src/filesysmaker.cpp \
    src/func.cpp \
    src/homepage.cpp \
    src/Input_Instance.cpp \
    src/keyhash.cpp \
    src/login_table.cpp \
    src/main.cpp \
    src/newuser.cpp \
    src/path_handle.cpp \
    src/server_window.cpp \
    src/shared.cpp \
    src/sharestring.cpp \
    src/SSL-Client.cpp \
    src/string_int.cpp \
    src/syncbox.cpp \
    src/time_handle.cpp \
    src/upload.cpp

FORMS    += \
    ui/dropbox2.ui \
    ui/homepage.ui \
    ui/newuser.ui \
    ui/server_window.ui \
    ui/shared.ui \
    ui/upload.ui

RESOURCES += \
    assets/dropboxresources.qrc\

DESTDIR = ./bin

HEADERS += \
    include/dropbox2.h \
    include/filehandle.h \
    include/fileinfo1.h \
    include/FileObjects.h \
    include/filesysmaker.h \
    include/func.h \
    include/homepage.h \
    include/Input_Instance.h \
    include/keyhash.h \
    include/login_table.h \
    include/newuser.h \
    include/path_handle.h \
    include/server_window.h \
    include/shared.h \
    include/sharestring.h \
    include/ssl-client.h \
    include/string_int.h \
    include/stringobject.h \
    include/time_handle.h \
    include/upload.h \
    include/variables.h
