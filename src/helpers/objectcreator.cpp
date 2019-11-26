#include "objectcreator.h"

STile ObjectCreator::createTile(int i, int j, TileType::Enum type, TileOrientation::Enum orientation)
{
    STile tile = STile(new Tile());
    tile->setPosition(QPoint(j*PX_TILE_SIZE, i*PX_TILE_SIZE));
    tile->setExplosionType(ExplosionType::NONE);
    tile->setScoredPoints(ScoredPoints::NONE);
    tile->setSize(QSize(PX_TILE_SIZE,PX_TILE_SIZE));
    tile->setType(type);
    tile->setOrientation(orientation);
    return tile;
}

SEnemyTank ObjectCreator::createEnemyTank(int i, int j, TankType::Enum type)
{
    SEnemyTank enemyTank = SEnemyTank(new EnemyTank());
    enemyTank->setPosition(QPoint(j*PX_TILE_SIZE, i*PX_TILE_SIZE));
    enemyTank->setSize(QSize(PX_TILE_SIZE,PX_TILE_SIZE));
    enemyTank->setAboutToAppear(true);
    enemyTank->setExplosionType(ExplosionType::TANK_EXPLOSION);
    enemyTank->setScoredPoints(ScoredPoints::Enum((int)type));
    enemyTank->setType(type);
    enemyTank->setBonus(false);
    enemyTank->setMoving(false);
    enemyTank->loadShell();
    enemyTank->setDirection(Direction::DOWN);

    if (type == TankType::HEAVY_TANK)
    {
        enemyTank->setHitPoints(ModelsProperties::HEAVY_TANK_HIT_POINTS);
    }
    else
    {
        enemyTank->setHitPoints(ModelsProperties::DEFAULT_TANK_HIT_POINTS);
    }


    if (type == TankType::MOTOR_TANK)
    {
        enemyTank->setSpeed(ModelsProperties::FAST_ENEMY_TANK_SPEED);
    }
    else
    {
        enemyTank->setSpeed(ModelsProperties::SLOW_ENEMY_TANK_SPEED);
    }

    return enemyTank;
}

SPlayerTank ObjectCreator::createPlayerTank(int playerNumber)
{
    SPlayerTank playerTank = SPlayerTank(new PlayerTank());

    QPoint position;

    position.setX(ModelsProperties::PLAYER_SPOT_POSITION_COLUMN*PX_TILE_SIZE);
    position.setY(ModelsProperties::PLAYER_SPOT_POSITION_ROW*PX_TILE_SIZE);
    playerTank->setPosition(position);
    playerTank->setSize(QSize(PX_TILE_SIZE,PX_TILE_SIZE));
    playerTank->setDirection(Direction::UP);
    playerTank->setPlayerNumber(playerNumber);
    playerTank->setAboutToAppear(true);
    playerTank->setExplosionType(ExplosionType::TANK_EXPLOSION);
    playerTank->setScoredPoints(ScoredPoints::NONE);
    playerTank->setNumberOfStars(0);
    playerTank->setMoving(false);
    playerTank->loadShell();
    playerTank->setInvulnerable(false);
    playerTank->setHitPoints(ModelsProperties::DEFAULT_TANK_HIT_POINTS);
    playerTank->setSpeed(ModelsProperties::PLAYER_TANK_SPEED);
    return playerTank;
}

SEagle ObjectCreator::createEagle()
{
    SEagle eagle = SEagle(new Eagle());

    QPoint position;

    position.setX(ModelsProperties::EAGLE_POSITION_COLUMN*PX_TILE_SIZE);
    position.setY(ModelsProperties::EAGLE_POSITION_ROW*PX_TILE_SIZE);
    eagle->setPosition(position);
    eagle->setExplosionType(ExplosionType::NONE);
    eagle->setScoredPoints(ScoredPoints::NONE);
    eagle->setSize(QSize(PX_TILE_SIZE,PX_TILE_SIZE));
    return eagle;
}

SPowerUp ObjectCreator::createPowerUp(int i, int j, PowerUpType::Enum type)
{
    SPowerUp powerUp = SPowerUp(new PowerUp());

    powerUp->setPosition(QPoint(j*PX_TILE_SIZE, i*PX_TILE_SIZE));
    powerUp->setExplosionType(ExplosionType::NONE);
    powerUp->setScoredPoints(ScoredPoints::FIVE_HUNDREDS);
    powerUp->setSize(QSize(PX_TILE_SIZE,PX_TILE_SIZE));
    powerUp->setType(type);

    return powerUp;
}

SBullet ObjectCreator::createBullet(STank tank)
{
    SBullet bullet = SBullet(new Bullet());

    QPoint direction = Converter::toVector(tank->direction());
    QPoint position = tank->position()+direction*(PX_TILE_SIZE/2-1);

    bullet->setPosition(position);
    bullet->setExplosionType(ExplosionType::BULLET_EXPLOSION);
    bullet->setScoredPoints(ScoredPoints::NONE);
    bullet->setSize(QSize(PX_TILE_SIZE/2,PX_TILE_SIZE/2));
    bullet->setDirection(tank->direction());
    bullet->setDealer(tank);
    bullet->setMoving(true);

    SPlayerTank playerTank = tank.objectCast<PlayerTank>();
    if (playerTank)
    {
        if (playerTank->numberOfStars() >= FAST_BULLETS_TRIGGER)
        {
            bullet->setSpeed(ModelsProperties::FAST_BULLET_SPEED);
        }
        else
        {
            bullet->setSpeed(ModelsProperties::SLOW_BULLET_SPEED);
        }
    }

    SEnemyTank enemyTank = tank.objectCast<EnemyTank>();
    if (enemyTank)
    {
        if (enemyTank->type() == TankType::RAPID_FIRE_TANK)
        {
            bullet->setSpeed(ModelsProperties::FAST_BULLET_SPEED);
        }
        else
        {
            bullet->setSpeed(ModelsProperties::SLOW_BULLET_SPEED);
        }
    }

    return bullet;
}
