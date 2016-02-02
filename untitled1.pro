TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    file_operation.c \
    command_line.c

HEADERS += \
    file_operation.h \
    data.h \
    command_line.h
