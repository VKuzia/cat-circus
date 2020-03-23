#-------------------------------------------------
#
# Project created by QtCreator 2020-03-06T23:09:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CatCircus
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        src/game/game.cpp \
        src/game/gamewidget.cpp \
#        src/game/minigame.cpp \
#        src/game/minigames/testminigame.cpp \
#        src/game/object.cpp \
        src/menu/aboutwidget.cpp \
        src/menu/main.cpp \
        src/menu/mainwindow.cpp \
        src/menu/settingswidget.cpp \
        src/utility/infomanager.cpp \
#        src/utility/physics.cpp \
#        src/utility/soundmanager.cpp \

HEADERS += \
        src/game/game.h \
        src/game/gamewidget.h \
#        src/game/minigame.h \
#        src/game/minigames/testminigame.h \
#        src/game/object.h \
        src/menu/aboutwidget.h \
        src/menu/mainwindow.h \
        src/menu/settingswidget.h \
        src/utility/infomanager.h \
#        src/utility/physics.h \
#        src/utility/soundmanager.h \

FORMS += \
        src/game/gamewidget.ui \
        src/menu/aboutwidget.ui \
        src/menu/mainwindow.ui \
        src/menu/settingswidget.ui

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    data/data.txt
