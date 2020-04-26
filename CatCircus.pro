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
        src/game/game_objects/backgroundobject.cpp \
        src/game/game_objects/clickableball.cpp \
    src/game/game_objects/pathobject.cpp \
        src/game/game_objects/timebar.cpp \
        src/game/gameobject.cpp \
        src/game/gameview.cpp \
        src/game/gamewidget.cpp \
        src/game/minigame.cpp \
        src/game/minigames/juggling/jugglingball.cpp \
        src/game/minigames/juggling/jugglingcat.cpp \
        src/game/minigames/juggling/jugglinghand.cpp \
        src/game/minigames/juggling/jugglingminigame.cpp \
        src/game/minigames/test/testminigame.cpp \
        src/game/minigames/trampoline/trampoline.cpp \
        src/game/minigames/trampoline/trampolinecat.cpp \
        src/game/minigames/trampoline/trampolineminigame.cpp \
        src/game/pausepage.cpp \
        src/game/physics/vector2d.cpp \
        src/game/scorepage.cpp \
        src/game/physics/physics.cpp \
        src/menu/aboutwidget.cpp \
        src/menu/main.cpp \
        src/menu/mainwindow.cpp \
        src/menu/settingswidget.cpp \

HEADERS += \
        src/game/game.h \
        src/game/game_objects/backgroundobject.h \
        src/game/game_objects/clickableball.h \
        src/game/game_objects/pathobject.h \
        src/game/game_objects/timebar.h \
        src/game/gameobject.h \
        src/game/gameview.h \
        src/game/gamewidget.h \
        src/game/minigame.h \
        src/game/minigames/juggling/jugglingball.h \
        src/game/minigames/juggling/jugglingcat.h \
        src/game/minigames/juggling/jugglinghand.h \
        src/game/minigames/juggling/jugglingminigame.h \
        src/game/minigames/test/testminigame.h \
        src/game/minigames/trampoline/trampoline.h \
        src/game/minigames/trampoline/trampolinecat.h \
        src/game/minigames/trampoline/trampolineminigame.h \
        src/game/pausepage.h \
        src/game/physics/vector2d.h \
        src/game/scorepage.h \
        src/game/physics/physics.h \
        src/menu/aboutwidget.h \
        src/menu/mainwindow.h \
        src/menu/settingswidget.h

FORMS += \
        src/game/gamewidget.ui \
        src/game/pausepage.ui \
        src/game/scorepage.ui \
        src/menu/aboutwidget.ui \
        src/menu/mainwindow.ui \
        src/menu/settingswidget.ui

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
