#ifndef MOVEMENTCOORDINATOR_H
#define MOVEMENTCOORDINATOR_H

#include <QObject>
#include "icoordinator.h"
#include "../global.h"
#include "../models/movingobject.h"
#include "../constants/definedconstants.h"

typedef QList<SInteractiveObject> ObjectList;
typedef QListIterator<SInteractiveObject> ObjectListIterator;

class MovementCoordinator : public QObject, public ICoordinator
{
    Q_OBJECT
public:
    MovementCoordinator();

    // ICoordinator interface
public:
    void initialize();
    void terminate();

signals:
    void objectMoved(MovingObject *mvObj, int distance, bool barrierIsReached) const;

private slots:
    void onTimerTriggered();

private:
    SGlobal mGlobal;

private: //processing
    void processCollisions() const;
    int processInteractions(SMovingObject mvObj) const;
    void validatePosition(SMovingObject mvObj) const;

private: //helping
    bool limitIsReached(const QRect &rect) const;
    ObjectList findCrossingObjects(const SMovingObject &mvObj) const;
    QRect getMovingArea(const SMovingObject &mvObj) const;
    QPoint transpose(const QPoint &p) const;
    QPoint crossProduct(const QPoint &p1, const QPoint &p2) const;
    QRect normalize(const QRect &r) const;
};

typedef QSharedPointer<MovementCoordinator> SMovementCoordintator;

#endif // MOVEMENTCOORDINATOR_H
