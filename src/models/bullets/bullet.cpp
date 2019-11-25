#include "bullet.h"

STank Bullet::dealer() const
{
    return mDealer;
}

void Bullet::setDealer(const STank &dealer)
{
    if (mDealer != dealer)
    {
        mDealer = dealer;
        emit dealerChanged();
    }
}

void Bullet::reachBarrier(int distance)
{
    MovingObject::reachBarrier(distance);
    setTerminateNextTurn(true);
}
