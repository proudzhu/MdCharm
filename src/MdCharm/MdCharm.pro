TEMPLATE = app

QT += core gui webkit network widgets webkitwidgets printsupport

CONFIG(debug, debug|release){ #debug
    DEFINES += MDCHARM_DEBUG
    TARGET = MdCharm_d
    DESTDIR = ../debug/
    LIBS += -L../debug -lcore -lcmark
} else { #release
    DEFINES += NDEBUG
    DEFINES += QT_NO_DEBUG_OUTPUT
    TARGET = MdCharm
    unix:TARGET = mdcharm
    DESTDIR = ../release/
    LIBS += -L../release -lcore -lcmark
}

unix: {
    LIBS += -lhunspell
    CONFIG(debug, debug|release){
        LIBS += -L../debug -lpcre16
    } else {
        LIBS += -L../release -lpcre16
    }
    CONFIG += link_pkgconfig
    PKGCONFIG += zlib glib-2.0
}

INCLUDEPATH += ../lib/core

version_h.target = version.h

unix:version_h.commands = python ../../src/MdCharm/version_h.py release

version_h.depends = version_h_nonexist
version_h.CONFIG += recursive

version_h_nonexist.commands= @echo generating version.h

QMAKE_EXTRA_TARGETS += version_h version_h_nonexist

PRE_TARGETDEPS += version.h

SOURCES += \
    main.cpp \
    mdcharmform.cpp \
    editareatabwidget.cpp \
    editareawidget.cpp \
    markdowneditareawidget.cpp \
    resource.cpp \
    browereditareawidget.cpp \
    utils.cpp \
    util/syntax/hightlighter.cpp \
    util/zip/zipwriter.cpp \
    util/odt/odtwriter.cpp \
    conf/configuredialog.cpp \
    configuration.cpp \
    conf/pages.cpp \
    baseeditor/baseeditor.cpp \
    about/aboutmdcharmdialog.cpp \
    util/gui/findandreplace.cpp \
    network/checkupdates.cpp \
    dock/projectdockwidget.cpp \
    util/gui/addnewfiledialog.cpp \
    util/gui/selectencodingdialog.cpp \
    util/gui/statusbarlabel.cpp \
    util/gui/gotodialog.cpp \
    util/spellcheck/spellchecker.cpp \
    baseeditor/markdowneditor.cpp \
    util/gui/exportdialog.cpp \
    util/sessionfileparser.cpp \
    mdcharmapplication.cpp \
    util/gui/insertlinkorpicturedialog.cpp \
    util/gui/renamefiledialog.cpp \
    util/spellcheck/spellcheckselectordialog.cpp \
    util/gui/markdowncheatsheetdialog.cpp \
    util/gui/insertcodedialog.cpp \
    util/gui/noticedialog.cpp \
    util/filesystemmodel.cpp \
    util/filesystemtreeview.cpp \
    util/rotationtoolbutton.cpp \
    baseeditor/baseautocompleter.cpp \
    baseeditor/markdownautocompleter.cpp \
    editareatabwidgetmanager.cpp \
    basewebview/basewebview.cpp \
    basewebview/markdownwebview.cpp \
    util/gui/newversioninfodialog.cpp \
    util/gui/exportdirectorydialog.cpp \
    util/gui/shortcutlineedit.cpp \
    dock/tocdockwidget.cpp \
    util/updatetocthread.cpp


HEADERS += \
    mdcharmform.h \
    editareatabwidget.h \
    editareawidget.h \
    markdowneditareawidget.h \
    resource.h \
    browereditareawidget.h \
    utils.h \
    util/syntax/hightlighter.h \
    util/zip/zipwriter.h \
    util/odt/odtwriter.h \
    conf/configuredialog.h \
    configuration.h \
    conf/pages.h \
    baseeditor/baseeditor.h \
    about/aboutmdcharmdialog.h \
    util/gui/findandreplace.h \
    network/checkupdates.h \
    dock/projectdockwidget.h \
    util/gui/addnewfiledialog.h \
    util/gui/selectencodingdialog.h \
    util/gui/statusbarlabel.h \
    util/gui/gotodialog.h \
    util/spellcheck/spellchecker.h \
    baseeditor/markdowneditor.h \
    util/gui/exportdialog.h \
    util/sessionfileparser.h \
    mdcharmapplication.h \
    util/gui/insertlinkorpicturedialog.h \
    util/gui/renamefiledialog.h \
    util/spellcheck/spellcheckselectordialog.h \
    util/gui/markdowncheatsheetdialog.h \
    util/gui/insertcodedialog.h \
    util/gui/noticedialog.h \
    util/filesystemmodel.h \
    util/filesystemtreeview.h \
    util/rotationtoolbutton.h \
    baseeditor/baseautocompleter.h \
    baseeditor/markdownautocompleter.h \
    editareatabwidgetmanager.h \
    basewebview/basewebview.h \
    basewebview/markdownwebview.h \
    util/gui/newversioninfodialog.h \
    util/gui/exportdirectorydialog.h \
    util/gui/shortcutlineedit.h \
    dock/tocdockwidget.h \
    util/updatetocthread.h


FORMS += \
    conf/environmentpage.ui \
    conf/texteditorpage.ui \
    about/aboutdialog.ui \
    util/gui/findandreplaceform.ui \
    dock/projectdockwidget.ui \
    util/gui/addnewfiledialog.ui \
    conf/stylespage.ui \
    util/gui/selectencodingdialog.ui \
    util/gui/gotodialog.ui \
    util/gui/exportdialog.ui \
    util/gui/insertlinkorpicturedialog.ui \
    util/gui/renamefiledialog.ui \
    util/spellcheck/spellcheckselectordialog.ui \
    util/gui/insertcodedialog.ui \
    util/gui/noticedialog.ui \
    util/gui/exportdirectorydialog.ui \
    dock/tocdockwidget.ui

RESOURCES += \
    $$PWD/../res/MdCharm.qrc
