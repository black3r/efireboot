TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
unix: {
    LIBS += -lefivar
    SOURCES += efi-linux.c
}

SOURCES += main.c

HEADERS += \
    efi.h

