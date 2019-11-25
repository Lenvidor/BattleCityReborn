#include "objectcoordinator.h"

ObjectCoordinator::ObjectCoordinator() : mGlobal(Global::getInstance())
{

}

/**********************************************
 * ORGINISING METHODS
 **********************************************/


void ObjectCoordinator::initialize()
{
    if (!mGlobal)
        return;

    if (mGlobal->interactionController)
    {
        QObject::connect(mGlobal->interactionController.data(),&InteractionController::bonusTankHit, this,&ObjectCoordinator::onBonusTankHit);
    }

    construct();
}

void ObjectCoordinator::terminate()
{
    if (!mGlobal)
        return;

    clear();

    if (mGlobal->interactionController)
    {
        QObject::disconnect(mGlobal->interactionController.data(),&InteractionController::bonusTankHit, this,&ObjectCoordinator::onBonusTankHit);
    }
}

void ObjectCoordinator::initPlayerTank()
{
    SPlayerTank tank = mObjectCreator->createPlayerTank();
    tank->setNumberOfStars(0);
    tank->setInvulnerable(true);

    mGlobal->resumableTimer->singleShot(INIT_INVULNERABILITY_TIMER_MSEC,tank.data(),SLOT(makeVulnerable()));
    addTank(tank);
    QObject::connect(tank.data(),&Tank::terminatedChanged,this,&ObjectCoordinator::onPlayerTankTerminated);
}

void ObjectCoordinator::createRandomPowerUp()
{
    onBonusTankHit();
}

void ObjectCoordinator::addEnemyTank(bool bonus)
{
    int i = 0;
    int j = ModelsProperties::ENEMY_SPOT_POSITION_ROW;

    switch (qrand()%3)
    {
    case 0:
    {
        i = ModelsProperties::ENEMY_FIRST_SPOT_POSITION_COLUMN;
        break;
    }
    case 1:
    {
        i = ModelsProperties::ENEMY_SECOND_SPOT_POSITION_COLUMN;
        break;
    }
    case 2:
    {
        i = ModelsProperties::ENEMY_THIRD_SPOT_POSITION_COLUMN;
        break;
    }
    }

    SEnemyTank tank = mObjectCreator->createEnemyTank(j,i,TankType::Enum(qrand()%4));
    tank->setBonus(bonus);
    tank->setDirection(Direction::DOWN);
    tank->setMoving(!mGlobal->powerUpCoordinator->stopActionBonus());
    addTank(tank);
    Object::connect(tank.data(),&EnemyTank::terminatedChanged,this,&ObjectCoordinator::onEnemyTankTerminated);
}

void ObjectCoordinator::construct()
{
    if (!mGlobal || !mGlobal->modelsContainer || !mGlobal->stageMapProvider)
        return;

    StageMap map = mGlobal->stageMapProvider->getStageMap();

    int tileCode;
    TileType::Enum tileType;
    TileOrientation::Enum tileOrientation;

    for (int i = 0; i < STAGE_MAP_SIZE; i++)
    {
        for (int j = 0; j < STAGE_MAP_SIZE; j++)
        {
            tileCode = map(i,j);
            tileOrientation = TileOrientation::Enum(tileCode & TILE_ORIENTATION_MASK);
            tileType = TileType::Enum(tileCode >> TILE_TYPE_SHIFT);
            processTileCode(i, j, tileType, tileOrientation);
        }
    }

    processBaseArea();
}

void ObjectCoordinator::clear()
{
    if (!mGlobal || !mGlobal->modelsContainer)
        return;

    auto iter = mGlobal->modelsContainer->getIterator();

    while (iter.hasNext())
    {
        iter.next();
        iter.remove();
    }
}


/**********************************************
 * PROCESSING METHODS
 **********************************************/

void ObjectCoordinator::addObject(SObject obj)
{
    QQmlEngine::setObjectOwnership(obj.data(),QQmlEngine::CppOwnership);
    mGlobal->modelsContainer->insert(obj);

    SInteractiveObject intObj = obj.objectCast<InteractiveObject>();
    if (intObj)
    {
        QObject::connect(intObj.data(),&InteractiveObject::terminatedChanged,this,&ObjectCoordinator::onObjectTerminated);
    }
}

void ObjectCoordinator::addTank(STank tank)
{
    mGlobal->resumableTimer->singleShot(APPEARANCE_TIME,tank.data(),SLOT(appear()));
    addObject(tank);
    QObject::connect(tank.data(),&Tank::shellLaunched,this,&ObjectCoordinator::onShellLaunched);
}

void ObjectCoordinator::processTileCode(int i, int j, TileType::Enum tileType, TileOrientation::Enum tileOrientation)
{
    SObject obj;

    if (!TileType::isValid(tileType))
    {
        tileType = TileType::NONE;
    }
    if (!TileOrientation::isValid(tileOrientation))
    {
        tileOrientation = TileOrientation::NONE;
    }

    switch (tileType)
    {
    case TileType::BRICK_TILE:
    case TileType::CONCRETE_TILE:
    {
        obj = mObjectCreator->createTile(i, j, tileType, tileOrientation);
        break;
    }
    case TileType::NONE:
        //do nothing
        break;
    }

    if (obj)
    {
        addObject(obj);
    }
}

void ObjectCoordinator::processBaseArea()
{
    SEagle eagle = mObjectCreator->createEagle();
    addObject(eagle);

    QObject::connect(eagle.data(),&Eagle::defeatedChanged,this,&ObjectCoordinator::onEagleDefeated);
}

void ObjectCoordinator::reconstructTile(int i, int j, TileType::Enum type, TileOrientation::Enum orientation)
{
    auto iter = mGlobal->modelsContainer->getIterator<Tile>();

    STile tile(nullptr);
    while (iter.hasNext())
    {
        if (iter.peekNext()->rect().contains(i*PX_TILE_SIZE,j*PX_TILE_SIZE))
        {
            tile = iter.next();
            break;
        }
        iter.next();
    }

    if (!tile)
    {
        tile = mObjectCreator->createTile(j,i,type,orientation);
        addObject(tile);
    }
    else
    {
        tile->setType(type);
        tile->setOrientation(orientation);
    }
}

void ObjectCoordinator::setInvulnerable(PlayerTank *tank, int msec)
{
    if (!tank || !mGlobal || !mGlobal->resumableTimer)
        return;

    mGlobal->resumableTimer->disconnect(tank,SLOT(makeVulnerable()));
    mGlobal->resumableTimer->connect(msec,tank,SLOT(makeVulnerable()));
    tank->setInvulnerable(true);
}

void ObjectCoordinator::reconstructBaseBorders(TileType::Enum type)
{
    int x = ModelsProperties::EAGLE_POSITION_COLUMN;
    int y = ModelsProperties::EAGLE_POSITION_ROW;

    reconstructTile(x-1,y,  type,TileOrientation::RIGHT);
    reconstructTile(x-1,y-1,type,TileOrientation::BOTTOM_RIGHT_CORNER);
    reconstructTile(x  ,y-1,type,TileOrientation::BOTTOM);
    reconstructTile(x+1,y-1,type,TileOrientation::BOTTOM_LEFT_CORNER);
    reconstructTile(x+1,y,  type,TileOrientation::LEFT);
}

/**********************************************
 * EVENT LISTENERS
 **********************************************/


void ObjectCoordinator::onBonusTankHit()
{
    auto iter = mGlobal->modelsContainer->getIterator<PowerUp>();

    if (iter.hasNext())
    {
        iter.next();
        iter.remove();
    }

    int i = qrand()%STAGE_MAP_SIZE;
    int j = qrand()%STAGE_MAP_SIZE;
    PowerUpType::Enum type = PowerUpType::MIN;

    switch (qrand()%8)
    {
    case 0:
    {
        type = PowerUpType::HELMET;
        break;
    }
    case 1:
    {
        type = PowerUpType::CLOCK;
        break;
    }
    case 2:
    {
        type = PowerUpType::TANK;
        break;
    }
    case 3:
    {
        type = PowerUpType::SHOVEL;
        break;
    }
    case 4:
    case 5:
    {
        type = PowerUpType::STAR;
        break;
    }
    case 6:
    case 7:
    {
        type = PowerUpType::SHELL;
        break;
    }
    }

    SPowerUp powerUp = mObjectCreator->createPowerUp(i,j,type);
    addObject(powerUp);
}

void ObjectCoordinator::onObjectTerminated()
{
    if (!mGlobal || !mGlobal->modelsContainer)
        return;

    mGlobal->modelsContainer->remove(qobject_cast<Object*>(QObject::sender()));
}

void ObjectCoordinator::onEagleDefeated()
{
    emit gameOverReached();
}

void ObjectCoordinator::onShellLaunched()
{
    STank tank = qobject_cast<Tank*>(QObject::sender())->sharedFromThis();
    SBullet bullet = mObjectCreator->createBullet(tank);
    addObject(bullet);
    QObject::connect(bullet.data(),&Bullet::terminatedChanged,tank.data(),&Tank::loadShell);
}

void ObjectCoordinator::onPlayerTankTerminated()
{
    if (mGlobal->playerInfo->lives() > 1)
    {
        mGlobal->resumableTimer->singleShot(APPEARANCE_DELAY, this, SLOT(initPlayerTank()));
        mGlobal->playerInfo->setLives(mGlobal->playerInfo->lives() - 1);
    }
    else
    {
        mGlobal->playerInfo->setLives(mGlobal->playerInfo->lives() - 1);
        emit gameOverReached();
    }
}

void ObjectCoordinator::onEnemyTankTerminated()
{
    auto iter = mGlobal->modelsContainer->getIterator<EnemyTank>();
    int tanksAvailable = mGlobal->stageInfo->tanksAvailable();

    if (!iter.hasNext() && tanksAvailable <= 0)
    {
        emit gameOverReached();
    }
}

