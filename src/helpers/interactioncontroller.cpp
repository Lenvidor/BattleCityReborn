#include "interactioncontroller.h"

/**********************************************
 * PROCESSING METHODS
 **********************************************/

InteractionController::InteractionController()
{
    mGlobal = Global::getInstance();
}

bool InteractionController::interact(SMovingObject mvObj, SInteractiveObject intObj, int interactDistance)
{
    if (mvObj.objectCast<Tank>())
    {
        if (intObj.objectCast<Tank>())
        {
            return true;
        }
        else if (intObj.objectCast<Bullet>())
        {
            STank tank = mvObj.objectCast<Tank>();
            SBullet bullet = intObj.objectCast<Bullet>();
            return interactTankBullet(tank,bullet);
        }
        else if (intObj.objectCast<Tile>())
        {
            return true;
        }
        else if (intObj.objectCast<Eagle>())
        {
            return true;
        }
        else if (intObj.objectCast<PowerUp>())
        {
            STank tank = mvObj.objectCast<Tank>();
            SPowerUp powerUp = intObj.objectCast<PowerUp>();
            return interactTankPowerUp(tank,powerUp);
        }
    }
    else if (mvObj.objectCast<Bullet>())
    {
        SBullet bullet = mvObj.objectCast<Bullet>();

        if (intObj.objectCast<Tank>())
        {
            STank tank = intObj.objectCast<Tank>();
            return interactTankBullet(tank,bullet);
        }
        else if (intObj.objectCast<Bullet>())
        {
            SBullet bullet2 = intObj.objectCast<Bullet>();
            return interactBulletBullet(bullet,bullet2);
        }
        else if (intObj.objectCast<Tile>())
        {
            STile tile = intObj.objectCast<Tile>();
            return interactBulletTile(bullet, tile, interactDistance);
        }
        else if (intObj.objectCast<Eagle>())
        {
            SEagle eagle = intObj.objectCast<Eagle>();
            return interactBulletEagle(bullet, eagle);
        }
    }

    return false;
}

bool InteractionController::interactTankBullet(STank tank, SBullet bullet)
{
    if (!tank || !bullet || bullet->terminateNextTurn())
        return false;

    if ((bool)tank.objectCast<PlayerTank>()^(bool)bullet->dealer().objectCast<PlayerTank>())
    {
        SPlayerTank playerTank = tank.objectCast<PlayerTank>();
        if (playerTank)
        {
            if (playerTank->invulnerable())
            {
                bullet->setExplosionType(ExplosionType::NONE);
            }
            else
            {
                playerTank->hit();
            }
            return true;
        }

        SEnemyTank enemyTank = tank.objectCast<EnemyTank>();
        if (enemyTank)
        {
            if (enemyTank->bonus())
            {
                enemyTank->setBonus(false);
                emit bonusTankHit();
            }
            tank->hit();
            return true;
        }

        bullet->setTerminateNextTurn(true);
    }

    return false;
}

bool InteractionController::interactTankPowerUp(STank tank, SPowerUp powerUp)
{
    if (!tank || !powerUp)
        return false;

    SPlayerTank playerTank = tank.objectCast<PlayerTank>();

    if (playerTank)
    {
        emit powerUpReached(playerTank.data(), powerUp.data());
    }

    return false;
}

bool InteractionController::interactBulletBullet(SBullet bullet1, SBullet bullet2)
{
    if (!bullet1 || !bullet2)
        return false;

    if ((bool)bullet1->dealer().objectCast<PlayerTank>()^(bool)bullet2->dealer().objectCast<PlayerTank>())
    {
        bullet1->setExplosionType(ExplosionType::NONE);
        bullet2->setExplosionType(ExplosionType::NONE);
        bullet2->terminate();
        return true;
    }

    return false;
}

bool InteractionController::interactBulletTile(SBullet bullet, STile tile, int interactDistance)
{
    if (!bullet || !tile)
        return false;

    STank dealer = bullet->dealer();

    if (!dealer)
        return false;

    SPlayerTank playerTank = dealer.objectCast<PlayerTank>();
    bool superBullet = playerTank && playerTank->numberOfStars() >= SUPER_BULLETS_TRIGGER;

    QRect destrArea = getDestructionArea(bullet,interactDistance,superBullet);

    auto iter = mGlobal->modelsContainer->getIterator<Tile>();

    while (iter.hasNext())
    {
        STile tempTile = iter.next();

        if (tempTile->intersects(destrArea))
        {
            if (superBullet || tempTile->type() == TileType::BRICK_TILE)
            {
                tempTile->destruct(destrArea);
            }
        }
    }

    return true;
}

bool InteractionController::interactBulletEagle(SBullet bullet, SEagle eagle)
{
    if (!bullet || !eagle)
        return false;

    eagle->defeat();

    return true;
}

/**********************************************
 * HELPING METHODS
 **********************************************/

QPoint InteractionController::transpose(const QPoint &p) const
{
    return QPoint(p.y(),p.x());
}

QPoint InteractionController::crossProduct(const QPoint &p1, const QPoint &p2) const
{
    return QPoint(p1.x()*p2.x(),p1.y()*p2.y());
}

QRect InteractionController::getDestructionArea(SBullet bullet, int interactDistance, bool superBullet)
{
    int bulletSize = superBullet ? SUPER_BULLET_SIZE : BULLET_SIZE;
    QPoint s = QPoint(bullet->width(),bullet->height()); // size in point form
    QPoint c = bullet->position(); //current position of bullet
    QPoint d = Converter::toVector(bullet->direction()); // direction in point form
    QPoint td = transpose(d); // transposed point form of direction

    //temporary points
    QPoint p = c+crossProduct(d,s)/2+d*interactDistance;
    QPoint tl = p-td*PX_TILE_SIZE/2;
    QPoint br = p+td*PX_TILE_SIZE/2+d*bulletSize;

    return normalize(QRect(tl,br)).adjusted(1,1,0,0);
}

QRect InteractionController::normalize(const QRect &r) const
{
    QRect rect = r;

    if (rect.top() > rect.bottom())
    {
        rect.setBottom(r.top());
        rect.setTop(r.bottom());
    }
    if (rect.left() > rect.right())
    {
        rect.setLeft(r.right());
        rect.setRight(r.left());
    }
    return rect;
}
