QT       += core gui svg multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = csgo_demovoice
TEMPLATE = app
RC_ICONS = appico.ico

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG  += c++11

SOURCES += \
        frmabout.cpp \
        frmmatch.cpp \
        frmplay.cpp \
        frmsettings.cpp \
        main.cpp \
        frmmain.cpp \
        match.cpp \
        memoryreader.cpp \
        saedialog.cpp \
        saetimehelper.cpp \
        settings.cpp \
        update.cpp \
        vdem.cpp

HEADERS += \
        build.h \
        frmabout.h \
        frmmain.h \
        frmmatch.h \
        frmplay.h \
        frmsettings.h \
        match.h \
        memoryreader.h \
        saedialog.h \
        saetimehelper.h \
        settings.h \
        update.h \
        vdem.h

FORMS   += \
        frmabout.ui \
        frmmain.ui \
        frmmatch.ui \
        frmplay.ui \
        frmsettings.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
