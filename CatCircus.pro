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
        src/game/backgroundobject.cpp \
        src/game/game.cpp \
        src/game/gameobject.cpp \
        src/game/gameview.cpp \
        src/game/gamewidget.cpp \
        src/game/minigame.cpp \
        src/game/minigames/juggling/jugglingball.cpp \
        src/game/minigames/juggling/jugglingcat.cpp \
        src/game/minigames/juggling/jugglinghand.cpp \
        src/game/minigames/juggling/jugglingminigame.cpp \
        src/game/minigames/trampoline/trampoline.cpp \
        src/game/minigames/trampoline/trampolinecat.cpp \
        src/game/minigames/trampoline/trampolineminigame.cpp \
        src/game/minigames/trampoline/trampolinepath.cpp \
        src/game/minigames/trampoline/trampolinetile.cpp \
        src/game/minigames/test/clickableball.cpp \
        src/game/minigames/test/testminigame.cpp \
        src/game/pausepage.cpp \
        src/game/physics/vector2d.cpp \
        src/game/pixmaploader.cpp \
        src/game/scorepage.cpp \
        src/game/physics/physics.cpp \
        src/game/timebar.cpp \
        src/menu/aboutwidget.cpp \
        src/menu/loadingwidget.cpp \
        src/menu/main.cpp \
        src/menu/mainwindow.cpp \
        src/menu/settingswidget.cpp \

HEADERS += \
        src/game/backgroundobject.h \
        src/game/game.h \
        src/game/gameobject.h \
        src/game/gameview.h \
        src/game/gamewidget.h \
        src/game/minigame.h \
        src/game/minigames/juggling/jugglingball.h \
        src/game/minigames/juggling/jugglingcat.h \
        src/game/minigames/juggling/jugglinghand.h \
        src/game/minigames/juggling/jugglingminigame.h \
        src/game/minigames/trampoline/trampoline.h \
        src/game/minigames/trampoline/trampolinecat.h \
        src/game/minigames/trampoline/trampolineminigame.h \
        src/game/minigames/trampoline/trampolinepath.h \
        src/game/minigames/trampoline/trampolinetile.h \
        src/game/minigames/test/clickableball.h \
        src/game/minigames/test/testminigame.h \
        src/game/pausepage.h \
        src/game/physics/vector2d.h \
        src/game/pixmaploader.h \
        src/game/scorepage.h \
        src/game/physics/physics.h \
        src/game/timebar.h \
        src/menu/aboutwidget.h \
        src/menu/loadingwidget.h \
        src/menu/mainwindow.h \
        src/menu/settingswidget.h

FORMS += \
        src/game/gamewidget.ui \
        src/game/pausepage.ui \
        src/game/scorepage.ui \
        src/menu/aboutwidget.ui \
        src/menu/loadingwidget.ui \
        src/menu/mainwindow.ui \
        src/menu/settingswidget.ui

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
