QT += core gui network widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    request.cpp \
    user.cpp

HEADERS += \
    mainwindow.h \
    request.h \
    user.h

FORMS += \
    mainwindow.ui

LIBS += -L$$PWD/openssl
LIBS += -lcrypto-1_1-x64
LIBS += -lssl-1_1-x64
