#include "game.h"

Game::Game() : mGlobal(Global::getInstance())
{
    mGlobal->movementCoordinator = SMovementCoordintator(new MovementCoordinator());
    mGlobal->objectCoordinator = SObjectCoordinator(new ObjectCoordinator());
    mGlobal->aiCoordinator = SAICoordinator(new AICoordinator());
    mGlobal->powerUpCoordinator = SPowerUpCoordinator(new PowerUpCoordinator());
    mGlobal->interactionController = SInteractionController(new InteractionController());
    mGlobal->modelsContainer = SModelsContainer(new ModelsContainer());
    mGlobal->resumableTimer = SResumableTimer(new ResumableTimer());
    mGlobal->playerInfo = SPlayerInfo(new PlayerInfo());
    mGlobal->stageInfo = SStageInfo(new StageInfo());
    mGlobal->stageMapProvider = SStageMapProvider(new StageMapProvider());

    emit stageInfoChanged();
    emit playerInfoChanged();
    emit modelsContainerChanged();

    QObject::connect(this,&Game::pausedChanged,this,&Game::onPausedChanged);
    QObject::connect(this,&Game::startedChanged,this,&Game::onStartedChanged);
    QObject::connect(this,&Game::readyChanged,this,&Game::onReadyChanged);
}

bool Game::paused()
{
    return mPaused;
}

bool Game::started()
{
    return mStarted;
}

bool Game::ready()
{
    return mReady;
}

bool Game::over()
{
    return mOver;
}

StageInfo *Game::stageInfo()
{
    if (!mGlobal || !mGlobal->stageInfo)
        return nullptr;

    return mGlobal->stageInfo.data();
}

PlayerInfo *Game::playerInfo()
{
    if (!mGlobal || !mGlobal->playerInfo)
        return nullptr;

    return mGlobal->playerInfo.data();
}

ModelsContainer *Game::modelsContainer()
{
    if (!mGlobal || !mGlobal->modelsContainer)
        return nullptr;

    return mGlobal->modelsContainer.data();
}

void Game::prepare()
{
    if (!mReady)
    {
        mReady = true;
        emit readyChanged();
    }
}

void Game::unprepare()
{
    if (mReady)
    {
        mReady = false;
        emit readyChanged();
    }
}

void Game::start()
{
    if (!mStarted)
    {
        mStarted = true;
        emit startedChanged();
    }
}

void Game::finish()
{
    if (mStarted)
    {
        mStarted = false;
        emit startedChanged();
    }
}

void Game::pause()
{
    if (!mPaused)
    {
        mPaused = true;
        emit pausedChanged();
    }
}

void Game::unpause()
{
    if (mPaused)
    {
        mPaused = false;
        emit pausedChanged();
    }
}

void Game::movePlayer(int direction)
{
    if (!mGlobal || !mGlobal->modelsContainer)
        return;

    auto iter = mGlobal->modelsContainer->getIterator<PlayerTank>();

    if (iter.hasNext())
    {
        SPlayerTank tank = iter.next();

        tank->setMoving(true);
        tank->setDirection(Direction::Enum(direction));
    }
}

void Game::stopMoving()
{
    if (!mGlobal || !mGlobal->modelsContainer)
        return;

    auto iter = mGlobal->modelsContainer->getIterator<PlayerTank>();

    if (iter.hasNext())
    {
        SPlayerTank tank = iter.next();

        tank->setMoving(false);
    }
}

void Game::fireFromPlayer()
{
    if (!mGlobal || !mGlobal->modelsContainer)
        return;

    auto iter = mGlobal->modelsContainer->getIterator<PlayerTank>();

    if (iter.hasNext())
    {
        SPlayerTank tank = iter.next();

        if (tank->numberOfStars() >= MULTIPLE_BULLETS_TRIGGER)
        {
            tank->loadShell();
        }
        tank->fireshot();
    }
}

void Game::upgradePlayer()
{
    auto iter = mGlobal->modelsContainer->getIterator<PlayerTank>();

    if (iter.hasNext())
    {
        SPlayerTank tank = iter.next();

        if (tank->numberOfStars() < MAX_NUMBER_OF_STARS)
        {
            tank->setNumberOfStars(tank->numberOfStars()+1);
        }
    }
}

void Game::randomPowerUp()
{
    mGlobal->objectCoordinator->createRandomPowerUp();
}

void Game::destroyPlayerTank()
{
    auto iter = mGlobal->modelsContainer->getIterator<PlayerTank>();

    if (iter.hasNext())
    {
        iter.next()->terminate();
    }
}

void Game::addEnemyPlayer()
{
    mGlobal->objectCoordinator->addEnemyTank(qrand()%2);
}

void Game::onPausedChanged()
{
    if (mPaused)
    {
        mGlobal->resumableTimer->stop();
    }
    else
    {
        mGlobal->resumableTimer->resume();
    }
}

void Game::onStartedChanged()
{
    if (mStarted)
    {
        mGlobal->stageInfo->setTanksAvailable(MAX_AVAILABLE_TANKS);
        mGlobal->playerInfo->setLives(DEFAULT_NUMBER_OF_LIVES);
        mGlobal->playerInfo->setScore(0);
        mGlobal->objectCoordinator->initPlayerTank();
        QObject::connect(mGlobal->objectCoordinator.data(),&ObjectCoordinator::gameOverReached,this,&Game::onGameOverReached);
        setOver(false);
    }
    else
    {
        pause();
        setOver(false);
        QObject::disconnect(mGlobal->objectCoordinator.data(),&ObjectCoordinator::gameOverReached,this,&Game::onGameOverReached);
        mGlobal->stageInfo->setTanksAvailable(0);
        mGlobal->playerInfo->setLives(0);
        mGlobal->playerInfo->setScore(0);
    }
}

void Game::onReadyChanged()
{
    if (mReady)
    {
        mGlobal->movementCoordinator->initialize();
        mGlobal->objectCoordinator->initialize();
        mGlobal->aiCoordinator->initialize();
        mGlobal->powerUpCoordinator->initialize();
        mGlobal->stageInfo->setStageNumber(1);
    }
    else
    {
        mGlobal->stageInfo->setStageNumber(1);
        mGlobal->movementCoordinator->terminate();
        mGlobal->objectCoordinator->terminate();
        mGlobal->aiCoordinator->terminate();
        mGlobal->powerUpCoordinator->terminate();
        mGlobal->resumableTimer->clear();
    }
}

void Game::onGameOverReached()
{
    setOver(true);
    mGlobal->resumableTimer->singleShot(3000,this,SLOT(finish()));
}

void Game::setOver(bool value)
{
    if (mOver != value)
    {
        mOver = value;
        emit overChanged();
    }
}
