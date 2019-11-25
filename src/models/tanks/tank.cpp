#include "tank.h"

int Tank::hitPoints() const
{
    return mHitPoints;
}

void Tank::setHitPoints(int value)
{
    if (mHitPoints != value)
    {
        mHitPoints = value;
        emit hitPointsChanged();
    }
}

bool Tank::aboutToAppear() const
{
    return mAboutToAppear;
}

void Tank::setAboutToAppear(bool value)
{
    if (mAboutToAppear != value)
    {
        mAboutToAppear = value;
        emit aboutToAppearChanged();
    }
}

bool Tank::intersects(const QRect &rect) const
{
    if (aboutToAppear())
    {
        return false;
    }
    else
    {
        return MovingObject::intersects(rect);
    }
}

bool Tank::moving() const
{
    if (aboutToAppear())
    {
        return false;
    }
    else
    {
        return MovingObject::moving();
    }
}

void Tank::hit()
{
    setHitPoints(hitPoints()-1);
    
    if (hitPoints() <= 0)
    {
        terminate();
    }
}

void Tank::fireshot()
{
    if (!aboutToAppear() && mShellLoaded)
    {
        mShellLoaded = false;
        emit shellLaunched();
    }
}

void Tank::loadShell()
{
    if (!mShellLoaded)
    {
        mShellLoaded = true;
    }
}

void Tank::appear()
{
    if (mAboutToAppear)
    {
        mAboutToAppear = false;
        emit aboutToAppearChanged();
    }
}

bool Tank::shellLoaded() const
{
    return mShellLoaded;
}
