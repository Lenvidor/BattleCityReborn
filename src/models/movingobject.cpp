#include "movingobject.h"

#define MSEC_IN_SEC 1000.0

MovingObject::MovingObject()
{
    QObject::connect(this,&MovingObject::positionChanged,this,&MovingObject::onPositionChanged);
}

int MovingObject::speed() const
{
    return mSpeed;
}

void MovingObject::setSpeed(int speed)
{
    if (mSpeed != speed)
    {
        mSpeed = speed;
        emit speedChanged();
    }
}

bool MovingObject::moving() const
{
    return mMoving;
}

void MovingObject::setMoving(bool moving)
{
    if (mMoving != moving)
    {
        mMoving = moving;
        emit movingChanged();
    }
}

void MovingObject::move(int msec)
{
    QPointF direction = Converter::toVectorF(mDirection);
    QPointF nextOriginalPosition = mOriginalPosition + direction*originalMoveDistance(msec);

    setPosition(Converter::toPoint(nextOriginalPosition));

    mOriginalPosition = nextOriginalPosition;
}

void MovingObject::reachBarrier(int distance)
{
    QPoint direction = Converter::toVector(this->direction());
    setPosition(position()+distance*direction);
}

int MovingObject::nextMoveDistance(int msec)
{
    qreal originalDistance = originalMoveDistance(msec);

    QPointF direction = Converter::toVectorF(this->direction());
    QPointF nextOriginalPosition = mOriginalPosition+direction*originalDistance;

    QPoint startPoint(Converter::toPoint(mOriginalPosition));
    QPoint endPoint(Converter::toPoint(nextOriginalPosition));

    return (startPoint - endPoint).manhattanLength();
}

Direction::Enum MovingObject::direction() const
{
    return mDirection;
}

void MovingObject::setDirection(const Direction::Enum &direction)
{
    if (Direction::isValid(direction) && mDirection != direction)
    {
        mDirection = direction;
        emit directionChanged();
    }
}

void MovingObject::onPositionChanged()
{
    mOriginalPosition.setX(qreal(x()));
    mOriginalPosition.setY(qreal(y()));
}

bool MovingObject::terminateNextTurn() const
{
    return mTerminateNextTurn;
}

void MovingObject::setTerminateNextTurn(bool value)
{
    if (mTerminateNextTurn != value)
    {
        mTerminateNextTurn = value;
    }
}

qreal MovingObject::originalMoveDistance(int msec)
{
    return qreal(msec*speed())/MSEC_IN_SEC;
}
