#-------------------------------------------------
#
# Project created by QtCreator 2016-04-27T16:10:29
#
#-------------------------------------------------

QT       += core gui xml remoteobjects websockets svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../ozwadmin
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    metadatawindow.cpp \
    util.cpp \
    logwindow.cpp

HEADERS  += mainwindow.h \
    metadatawindow.h \
    util.h \
    logwindow.h \

FORMS    += mainwindow.ui \
    metadatawindow.ui

LIBS += ../devicedb-lib/libdevicedb-lib.a ../ozwadmin-widgets/libozwadmin-widgets.a
INCLUDEPATH += ../devicedb-lib ../ozwadmin-widgets

ozwconfig.target=config/qrc_ozwconfig.cpp
ozwconfig.commands=cp -R ../../open-zwave/config config/ && cd config && $$[QT_INSTALL_BINS]/rcc -project -o ozwconfig.qrc && $$[QT_INSTALL_BINS]/rcc --name="ozwconfig" --root="/config/" ozwconfig.qrc -o qrc_ozwconfig.cpp

QMAKE_EXTRA_TARGETS += ozwconfig
PRE_TARGETDEPS += config/qrc_ozwconfig.cpp
SOURCES += config/qrc_ozwconfig.cpp

macx: {
    QMAKE_CXXFLAGS += -F../../qt-openzwave/qt-openzwave/
    LIBS += -framework IOKit -framework CoreFoundation
    LIBS += -F../../qt-openzwave/qt-openzwave/ -framework qt-openzwave
    BUNDLE.files = ../../qt-openzwave/qt-openzwave/qt-openzwave.framework/
    BUNDLE.path = Contents/Frameworks/qt-openzwave.framework/
    LIBOZW.files = ../../open-zwave/libopenzwave-1.6.dylib
    LIBOZW.path = Contents/Frameworks/
    QMAKE_BUNDLE_DATA += BUNDLE LIBOZW
    ICON = res/ozw_logo.icns
} else {
    LIBS += -L../../qt-openzwave/qt-openzwave/ -lqt-openzwave -L../../open-zwave/ -lopenzwave -lresolv
    INCLUDEPATH += ../../qt-openzwave/qt-openzwave/include/
}

RESOURCES += \
    ozwadmin-main.qrc \
