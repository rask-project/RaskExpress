#QT -= gui
QT += network gui

QMAKE_CXXFLAGS += -std=c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    $$PWD/src/config.cpp \
    $$PWD/src/httpparser.cpp \
    $$PWD/src/httprequest.cpp \
    $$PWD/src/qexpress.cpp \
    $$PWD/src/qexpressserver.cpp \
    $$PWD/src/requeststatic.cpp \
    $$PWD/src/response.cpp \
    $$PWD/src/router.cpp \
    $$PWD/src/urlparser.cpp

HEADERS += \
    $$PWD/src/config.h \
    $$PWD/src/httpparser.h \
    $$PWD/src/httprequest.h \
    $$PWD/src/qexpress.h \
    $$PWD/src/qexpress_global.h \
    $$PWD/src/qexpressserver.h \
    $$PWD/src/qexpress_consts.h \
    $$PWD/src/request.h \
    $$PWD/src/requeststatic.h \
    $$PWD/src/response.h \
    $$PWD/src/router.h \
    $$PWD/src/urlparser.h

QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
