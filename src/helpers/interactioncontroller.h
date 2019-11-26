#pragma once

#include <QObject>
#include <QSharedPointer>
#include "../global.h"
#include "../models/movingobject.h"
#include "../models/bullets/bullet.h"
#include "../models/tanks/tank.h"
#include "../models/tanks/enemytank.h"
#include "../models/tanks/playertank.h"
#include "../models/others/eagle.h"
#include "../models/others/powerup.h"
#include "../models/tiles/tile.h"
#include "../constants/definedconstants.h"

class InteractionController : public QObject
{
    Q_OBJECT
public:
    InteractionController();
    bool interact(SMovingObject mvObj, SInteractiveObject intObj, int interactDistance);

signals:
    void bonusTankHit();
    void powerUpReached(PlayerTank *tank, PowerUp *powerUp);

private: //processing
    bool interactTankBullet(STank tank, SBullet bullet);
    bool interactTankPowerUp(STank tank, SPowerUp powerUp);
    bool interactBulletBullet(SBullet bullet1, SBullet bullet2);
    bool interactBulletTile(SBullet bullet, STile tile, int interactDistance);
    bool interactBulletEagle(SBullet bullet, SEagle eagle);

private: //helping
    QRect getDestructionArea(SBullet bullet, int interactDistance, bool superBullet);
    QRect normalize(const QRect &r) const;
    QPoint transpose(const QPoint &p) const;
    QPoint crossProduct(const QPoint &p1, const QPoint &p2) const;

private:
    SGlobal mGlobal;
};

typedef QSharedPointer<InteractionController> SInteractionController;
