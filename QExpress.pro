QT -= gui
QT += network

TEMPLATE = lib
DEFINES += QEXPRESS_LIBRARY

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
    src/qexpress.cpp \
    src/qexpressserver.cpp

HEADERS += \
    src/qexpress.h \
    src/qexpress_global.h \
    src/qexpressserver.h

# Default rules for deployment
macx {
    headers.path   = /usr/local/lib/qexpress
    headers.files += $$HEADERS
    target.path    = /usr/local/lib
}

QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

!isEmpty(target.path): INSTALLS += target
