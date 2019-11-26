#include "powerupcoordinator.h"

PowerUpCoordinator::PowerUpCoordinator()
{
    mGlobal = Global::getInstance();
}

/**********************************************
 * ORGINISING METHODS
 **********************************************/

void PowerUpCoordinator::initialize()
{
    QObject::connect(mGlobal->interactionController.data(),&InteractionController::powerUpReached, this,&PowerUpCoordinator::onPowerUpReached);
}

void PowerUpCoordinator::terminate()
{
    QObject::disconnect(mGlobal->interactionController.data(),&InteractionController::powerUpReached, this,&PowerUpCoordinator::onPowerUpReached);
}

/**********************************************
 * PROCESSING METHODS
 **********************************************/

void PowerUpCoordinator::processPowerUp(PlayerTank *tank, PowerUp *powerUp)
{
    if (!tank || !powerUp)
        return;

    switch (powerUp->type())
    {
    case PowerUpType::CLOCK:
    {
        activateStopActionBonus();
        break;
    }
    case PowerUpType::SHELL:
    {
        activateShellBonus();
        break;
    }
    case PowerUpType::SHOVEL:
    {
        activateShovelBonus();
        break;
    }
    case PowerUpType::TANK:
    {
        activateTankBonus();
        break;
    }
    case PowerUpType::STAR:
    {
        activateStarBonus(tank);
        break;
    }
    case PowerUpType::HELMET:
    {
        activateHelmetBonus(tank);
        break;
    }
    }

    powerUp->terminate();
}

void PowerUpCoordinator::activateStarBonus(PlayerTank *tank)
{
    if (!tank)
        return;

    tank->setNumberOfStars(qMin(MAX_NUMBER_OF_STARS,tank->numberOfStars()+1));
}

void PowerUpCoordinator::activateHelmetBonus(PlayerTank *tank)
{
    if (!tank)
        return;

    mGlobal->objectCoordinator->setInvulnerable(tank,HELMET_TIMER_MSEC);
}

void PowerUpCoordinator::activateStopActionBonus()
{
    if (!mGlobal || !mGlobal->modelsContainer || !mGlobal->resumableTimer)
        return;

    mGlobal->resumableTimer->singleShot(STOP_ACTION_TIMER_MSEC,this,SLOT(onStopActionBonusFinished()));

    mStopActionBonus = true;

    auto iter = mGlobal->modelsContainer->getIterator<EnemyTank>();
    while (iter.hasNext())
    {
        SEnemyTank tank = iter.next();
        tank->setMoving(false);
    }
}

void PowerUpCoordinator::activateShellBonus()
{
    if (!mGlobal || !mGlobal->modelsContainer)
        return;

    auto iter = mGlobal->modelsContainer->getIterator<EnemyTank>();
    while (iter.hasNext())
    {
        SEnemyTank tank = iter.next();
        tank->setScoredPoints(ScoredPoints::NONE);
        tank->terminate();
    }
}

void PowerUpCoordinator::activateTankBonus()
{
    if (!mGlobal || !mGlobal->playerInfo)
        return;

    mGlobal->playerInfo->setLives(qMin(MAX_NUMBER_OF_LIVES,mGlobal->playerInfo->lives()+1));
}

void PowerUpCoordinator::activateShovelBonus()
{
    if (!mGlobal || !mGlobal->modelsContainer || !mGlobal->resumableTimer)
        return;

    mGlobal->objectCoordinator->reconstructBaseBorders(TileType::CONCRETE_TILE);

    mGlobal->resumableTimer->disconnect(this,SLOT(aboutToStopShovelBonus()));
    mGlobal->resumableTimer->disconnect(this,SLOT(stopShovelBonus()));
    mGlobal->resumableTimer->disconnect(this,SLOT(blinkShovelBonus()));

    mGlobal->resumableTimer->connect(SHOVEL_TIMER_MSEC,this,SLOT(aboutToStopShovelBonus()));
}

void PowerUpCoordinator::aboutToStopShovelBonus()
{
    if (!mGlobal || !mGlobal->modelsContainer || !mGlobal->resumableTimer) {
        return;
    }

    mCurrentBrickBase = true;
    mGlobal->objectCoordinator->reconstructBaseBorders(TileType::BRICK_TILE);

    mGlobal->resumableTimer->disconnect(this,SLOT(aboutToStopShovelBonus()));
    mGlobal->resumableTimer->connect(BASE_WALL_FINITE_TIMER_MSEC,this,SLOT(stopShovelBonus()));
    mGlobal->resumableTimer->connect(BASE_WALL_BLINK_TIMER_MSEC,this,SLOT(blinkShovelBonus()));
}

void PowerUpCoordinator::stopShovelBonus()
{
    mGlobal->resumableTimer->disconnect(this,SLOT(stopShovelBonus()));
    mGlobal->resumableTimer->disconnect(this,SLOT(blinkShovelBonus()));
    mGlobal->objectCoordinator->reconstructBaseBorders(TileType::BRICK_TILE);
}

void PowerUpCoordinator::blinkShovelBonus()
{
    mCurrentBrickBase = !mCurrentBrickBase;
    mGlobal->objectCoordinator->reconstructBaseBorders(mCurrentBrickBase ? TileType::BRICK_TILE : TileType::CONCRETE_TILE);
}

bool PowerUpCoordinator::stopActionBonus() const
{
    return mStopActionBonus;
}

void PowerUpCoordinator::finishStopActionBonus()
{
    if (!mGlobal || !mGlobal->modelsContainer)
        return;

    mStopActionBonus = false;

    auto iter = mGlobal->modelsContainer->getIterator<EnemyTank>();
    while (iter.hasNext())
    {
        SEnemyTank tank = iter.next();
        tank->setMoving(true);
    }
}

/**********************************************
 * EVENT LISTENERS
 **********************************************/

void PowerUpCoordinator::onPowerUpReached(PlayerTank *tank, PowerUp *powerUp)
{
    processPowerUp(tank,powerUp);
}

void PowerUpCoordinator::onStopActionBonusFinished()
{
    finishStopActionBonus();
}
