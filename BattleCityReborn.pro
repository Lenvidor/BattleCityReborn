TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    src/game.cpp \
    src/registrar.cpp \
    src/coordinators/movementcoordinator.cpp \
    src/coordinators/objectcoordinator.cpp \
    src/helpers/interactioncontroller.cpp \
    src/models/object.cpp \
    src/models/interactiveobject.cpp \
    src/models/movingobject.cpp \
    src/helpers/converter.cpp \
    src/models/tanks/tank.cpp \
    src/models/tanks/playertank.cpp \
    src/models/tanks/enemytank.cpp \
    src/models/tiles/tile.cpp \
    src/models/bullets/bullet.cpp \
    src/models/others/eagle.cpp \
    src/containers/modelscontainer.cpp \
    src/global.cpp \
    src/helpers/resumabletimer.cpp \
    src/models/others/powerup.cpp \
    src/metadata/playerinfo.cpp \
    src/metadata/stageinfo.cpp \
    src/helpers/objectcreator.cpp \
    src/helpers/stagemapprovider.cpp \
    src/coordinators/aicoordinator.cpp \
    src/coordinators/powerupcoordinator.cpp

RESOURCES += \
    resources.qrc

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/game.h \
    src/registrar.h \
    src/coordinators/icoordinator.h \
    src/coordinators/movementcoordinator.h \
    src/coordinators/objectcoordinator.h \
    src/helpers/interactioncontroller.h \
    src/models/object.h \
    src/models/interactiveobject.h \
    src/models/movingobject.h \
    src/enums/direction.h \
    src/helpers/converter.h \
    src/models/tanks/tank.h \
    src/models/tanks/playertank.h \
    src/models/tanks/enemytank.h \
    src/enums/tanktype.h \
    src/models/tiles/tile.h \
    src/constants/definedconstants.h \
    src/enums/tileorientation.h \
    src/enums/tiletype.h \
    src/models/bullets/bullet.h \
    src/models/others/eagle.h \
    src/containers/modelscontainer.h \
    src/containers/containeriterator.h \
    src/containers/templatedefinitions.h \
    src/global.h \
    src/helpers/resumabletimer.h \
    src/models/others/powerup.h \
    src/enums/poweruptype.h \
    src/metadata/playerinfo.h \
    src/metadata/stageinfo.h \
    src/helpers/objectcreator.h \
    src/constants/modelsproperties.h \
    src/helpers/stagemapprovider.h \
    src/enums/explosiontype.h \
    src/enums/scoredpoints.h \
    src/enums/z.h \
    src/coordinators/aicoordinator.h \
    src/containers/callbackcontainer.h \
    src/coordinators/powerupcoordinator.h
