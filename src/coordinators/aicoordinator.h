#ifndef AICOORDINATOR_H
#define AICOORDINATOR_H

#include <QObject>
#include "../models/tanks/enemytank.h"
#include "icoordinator.h"
#include "../global.h"

class AICoordinator : public QObject, public ICoordinator
{
    Q_OBJECT
public:
    AICoordinator();
    void initialize();
    void terminate();

private slots:
    void onObjectMoved(MovingObject *mvObj, int distance, bool barrierIsReached);
    void onTimerTriggered();
    void onRespawnTriggered();

private:
    SGlobal mGlobal;

    void invertDirection(EnemyTank *tank);
    void changeDirection(EnemyTank *tank);
    void setRandomDirection(EnemyTank *tank);
    void setDirectionToEagle(EnemyTank *tank);
    void setDirectionToPlayer(EnemyTank *tank);
    void setDirectionTo(SObject obj, EnemyTank *tank);
};

typedef QSharedPointer<AICoordinator> SAICoordinator;

#endif // AICOORDINATOR_H
