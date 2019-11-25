#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QSharedPointer>
#include <QList>
#include "helpers/resumabletimer.h"
#include "helpers/stagemapprovider.h"
#include "containers/modelscontainer.h"
#include "coordinators/icoordinator.h"
#include "metadata/playerinfo.h"
#include "metadata/stageinfo.h"

class MovementCoordinator;
class ObjectCoordinator;
class AICoordinator;
class PowerUpCoordinator;
class InteractionController;
typedef QSharedPointer<MovementCoordinator> SMovementCoordintator;
typedef QSharedPointer<ObjectCoordinator> SObjectCoordinator;
typedef QSharedPointer<AICoordinator> SAICoordinator;
typedef QSharedPointer<PowerUpCoordinator> SPowerUpCoordinator;
typedef QSharedPointer<InteractionController> SInteractionController;

class Global : public QObject
{
    Q_OBJECT
    Global(){}
public:
    static QSharedPointer<Global> getInstance();
private:
    static QSharedPointer<Global> mInstance;

public:
    SMovementCoordintator movementCoordinator;
    SObjectCoordinator objectCoordinator;
    SAICoordinator aiCoordinator;
    SPowerUpCoordinator powerUpCoordinator;
    SInteractionController interactionController;
    SModelsContainer modelsContainer;
    SResumableTimer resumableTimer;
    SStageInfo stageInfo;
    SPlayerInfo playerInfo;
    SStageMapProvider stageMapProvider;
};

typedef QSharedPointer<Global> SGlobal;

#include "coordinators/movementcoordinator.h"
#include "coordinators/objectcoordinator.h"
#include "coordinators/aicoordinator.h"
#include "coordinators/powerupcoordinator.h"
#include "helpers/interactioncontroller.h"

#endif // GLOBAL_H
