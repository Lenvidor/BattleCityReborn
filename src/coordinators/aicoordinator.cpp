#include "aicoordinator.h"

#define MSEC_IN_SEC 1000.0


AICoordinator::AICoordinator()
{
    mGlobal = Global::getInstance();
}

void AICoordinator::initialize()
{
    QObject::connect(mGlobal->movementCoordinator.data(),&MovementCoordinator::objectMoved, this,&AICoordinator::onObjectMoved);
    mGlobal->resumableTimer->connect(MV_TIMER_MSEC,this,SLOT(onTimerTriggered()));
    mGlobal->resumableTimer->connect(ENEMY_RESPAWN_TIMER_MSEC,this,SLOT(onRespawnTriggered()));
}

void AICoordinator::terminate()
{
    QObject::disconnect(mGlobal->movementCoordinator.data(),&MovementCoordinator::objectMoved, this,&AICoordinator::onObjectMoved);
    mGlobal->resumableTimer->disconnect(this,SLOT(onTimerTriggered()));
}

void AICoordinator::onObjectMoved(MovingObject *mvObj, int distance, bool barrierIsReached)
{
    EnemyTank *tank = qobject_cast<EnemyTank*>(mvObj);

    if (!tank)
        return;

    if (qrand()%PX_TILE_SIZE*8 < distance)
    {
        changeDirection(tank);
    }
    else if (barrierIsReached && qrand()%4 < qreal(60*MV_TIMER_MSEC)/MSEC_IN_SEC)
    {
        if (tank->x() % TURN_RATE != 0 || tank->y() % TURN_RATE != 0)
        {
            invertDirection(tank);
        }
        else
        {
            changeDirection(tank);
        }
    }
}

void AICoordinator::onTimerTriggered()
{
    if (mGlobal->powerUpCoordinator->stopActionBonus())
        return;

    auto iter = mGlobal->modelsContainer->getIterator<EnemyTank>();

    while (iter.hasNext())
    {
        SEnemyTank tank = iter.next();

        if (qrand()%32 < qreal(60*MV_TIMER_MSEC)/MSEC_IN_SEC)
        {
            tank->fireshot();
        }
    }
}

void AICoordinator::onRespawnTriggered()
{
    auto iter = mGlobal->modelsContainer->getIterator<EnemyTank>();
    int counter = 0;

    while (iter.hasNext())
    {
        iter.next();
        counter++;
    }

    int ta = mGlobal->stageInfo->tanksAvailable();

    if (counter >= 4 || ta <= 0)
        return;

    bool bonus = (ta - 3) % 7 == 0;

    mGlobal->objectCoordinator->addEnemyTank(bonus);
    mGlobal->stageInfo->setTanksAvailable(ta-1);
}

void AICoordinator::invertDirection(EnemyTank *tank)
{
    switch (tank->direction())
    {
    case Direction::UP:
    {
        tank->setDirection(Direction::DOWN);
        break;
    }
    case Direction::DOWN:
    {
        tank->setDirection(Direction::UP);
        break;
    }
    case Direction::LEFT:
    {
        tank->setDirection(Direction::RIGHT);
        break;
    }
    case Direction::RIGHT:
    {
        tank->setDirection(Direction::LEFT);
        break;
    }
    }
}

void AICoordinator::setRandomDirection(EnemyTank *tank)
{
    int direction = (int)tank->direction();
    int min = (int)Direction::MIN;
    int max = (int)Direction::MAX;

    direction = (direction+qrand()%(max-min)+1)%(max-min+1);
    tank->setDirection(Direction::Enum(direction));
}

void AICoordinator::setDirectionToEagle(EnemyTank *tank)
{
    auto iter = mGlobal->modelsContainer->getIterator<Eagle>();

    if (iter.hasNext())
    {
        SEagle eagle = iter.next();

        setDirectionTo(eagle, tank);
    }
}

void AICoordinator::setDirectionToPlayer(EnemyTank *tank)
{
    auto iter = mGlobal->modelsContainer->getIterator<PlayerTank>();

    if (iter.hasNext())
    {
        SPlayerTank playerTank = iter.next();

        setDirectionTo(playerTank, tank);
    }
}

void AICoordinator::setDirectionTo(SObject obj, EnemyTank *tank)
{
    if (!obj || !tank)
        return;

    if (obj->y() > tank->y())
    {
        tank->setDirection(Direction::UP);
    }
    else if (obj->y() < tank->y())
    {
        tank->setDirection(Direction::DOWN);
    }
    else if (obj->x() > tank->x())
    {
        tank->setDirection(Direction::LEFT);
    }
    else if (obj->x() < tank->x())
    {
        tank->setDirection(Direction::RIGHT);
    }
}

void AICoordinator::changeDirection(EnemyTank *tank)
{
    switch (qrand()%5)
    {
    case 0:
    {
        setRandomDirection(tank);
        break;
    }
    case 1:
    case 2:
    {
        setDirectionToEagle(tank);
        break;
    }
    case 3:
    case 4:
    {
        setDirectionToPlayer(tank);
        break;
    }
    }

    setRandomDirection(tank);
}
