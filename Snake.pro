QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/candycontroller.cpp \
    controller/housecontroller.cpp \
    controller/snakecontroller.cpp \
    main.cpp \
    meta/meta.cpp \
    model/cabin.cpp \
    model/firmwall.cpp \
    model/inch.cpp \
    model/poison.cpp \
    model/python.cpp \
    model/squarewindow.cpp \
    model/sweet.cpp \
    view/game.cpp \
    view/gameview.cpp \
    view/mainview.cpp

HEADERS += \
    controller/candycontroller.h \
    controller/housecontroller.h \
    controller/snakecontroller.h \
    enums/position.h \
    enums/state.h \
    enums/value.h \
    meta/meta.h \
    model/cabin.h \
    model/candy.h \
    model/firmwall.h \
    model/house.h \
    model/inch.h \
    model/part.h \
    model/poison.h \
    model/python.h \
    model/snake.h \
    model/squarewindow.h \
    model/sweet.h \
    model/wall.h \
    model/window.h \
    view/game.h \
    view/gameview.h \
    view/mainview.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
