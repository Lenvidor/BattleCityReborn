#ifndef BULLET_H
#define BULLET_H

#include "../movingobject.h"
#include "../tanks/tank.h"

class Bullet : public MovingObject
{
    Q_OBJECT

public:
    STank dealer() const;
    void setDealer(const STank &dealer);
    void reachBarrier(int distance);

signals:
    void dealerChanged();

private:
    STank mDealer;
};

Q_DECLARE_METATYPE(Bullet *)
typedef QSharedPointer<Bullet> SBullet;

#endif // BULLET_H
