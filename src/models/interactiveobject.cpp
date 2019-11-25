#include "interactiveobject.h"


void InteractiveObject::terminate()
{
    if (!mTerminated)
    {
        mTerminated = true;
        emit terminatedChanged();
    }
}

bool InteractiveObject::terminated() const
{
    return mTerminated;
}

bool InteractiveObject::intersects(const QRect &rect) const
{
    return this->rect().intersects(rect);
}

bool InteractiveObject::intersects(const InteractiveObject *obj) const
{
    return intersects(obj->rect());
}

bool InteractiveObject::intersects(const QSharedPointer<InteractiveObject> &obj) const
{
    return intersects(obj->rect());
}

ExplosionType::Enum InteractiveObject::explosionType() const
{
    return mExplosionType;
}

void InteractiveObject::setExplosionType(const ExplosionType::Enum &value)
{
    if (ExplosionType::isValid(value) && mExplosionType != value)
    {
        mExplosionType = value;
        emit explosionTypeChanged();
    }
}

ScoredPoints::Enum InteractiveObject::scoredPoints() const
{
    return mScoredPoints;
}

void InteractiveObject::setScoredPoints(const ScoredPoints::Enum &value)
{
    if (ScoredPoints::isValid(value) && mScoredPoints != value)
    {
        mScoredPoints = value;
        emit scoredPointsChanged();
    }
}
