#pragma once

#include <QPointF>
#include <QtMath>
#include "../enums/direction.h"
#include "../helpers/converter.h"
#include "interactiveobject.h"

class MovingObject : public InteractiveObject
{
    Q_OBJECT
public:
    MovingObject();

    Q_PROPERTY(bool moving READ moving NOTIFY movingChanged)
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(Direction::Enum direction READ direction NOTIFY directionChanged)

    int speed() const;
    void setSpeed(int speed);

    virtual bool moving() const;
    void setMoving(bool moving);

    void move(int msec);
    virtual void reachBarrier(int distance);
    int nextMoveDistance(int msec);

    Direction::Enum direction() const;
    void setDirection(const Direction::Enum &direction);

    bool terminateNextTurn() const;
    void setTerminateNextTurn(bool terminateNextTurn);

signals:
    void speedChanged();
    void movingChanged();
    void directionChanged();

private slots:
    void onPositionChanged();

private:
    bool mMoving;
    bool mTerminateNextTurn { false };
    int mSpeed;
    QPointF mOriginalPosition;
    Direction::Enum mDirection;

    qreal originalMoveDistance(int msec);
};

Q_DECLARE_METATYPE(MovingObject *)
typedef QSharedPointer<MovingObject> SMovingObject;
