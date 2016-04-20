TEMPLATE = lib

TARGET = core

CONFIG += warn_off

unix: CONFIG += static

CONFIG(release, debug|release){
    DESTDIR = ../release
    LIBS += -lhunspell -lglib-2.0
} else {
    DESTDIR = ../debug
    LIBS += -lhunspell -lglib-2.0
}

CONFIG += link_pkgconfig
PKGCONFIG += zlib glib-2.0


HEADERS += \
    core/markdowntohtml.h \
    core/languagedefinationxmlparser.h \
    core/codesyntaxhighlighter.h

SOURCES += \
    core/markdowntohtml.cpp \
    core/languagedefinationxmlparser.cpp \
    core/codesyntaxhighlighter.cpp \
    core/commonmark.cpp

