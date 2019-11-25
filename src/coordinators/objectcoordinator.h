#ifndef OBJECTCOORDINATOR_H
#define OBJECTCOORDINATOR_H

#include <QObject>
#include <QtQml>
#include "icoordinator.h"
#include "../helpers/objectcreator.h"
#include "../global.h"

class ObjectCoordinator : public QObject, public ICoordinator
{
    Q_OBJECT
public:
    ObjectCoordinator();

    void initialize();
    void terminate();

    void createRandomPowerUp();
    void reconstructBaseBorders(TileType::Enum type);
    void setInvulnerable(PlayerTank *tank, int msec);

public slots:
    void addEnemyTank(bool bonus);
    void initPlayerTank();

signals:
    void gameOverReached();

private slots:
    void onBonusTankHit();
    void onObjectTerminated();
    void onEagleDefeated();
    void onShellLaunched();
    void onPlayerTankTerminated();
    void onEnemyTankTerminated();

private:
    SGlobal mGlobal;
    SObjectCreator mObjectCreator{ new ObjectCreator() };

private:
    void construct();

    void reconstructTile(int i, int j, TileType::Enum type, TileOrientation::Enum orientation);

    void processTileCode(int i, int j, TileType::Enum tileType, TileOrientation::Enum tileOrientation);
    void processBaseArea();

    void clear();

    void addObject(SObject obj);
    void addTank(STank tank);
};

typedef QSharedPointer<ObjectCoordinator> SObjectCoordinator;

#endif // OBJECTCOORDINATOR_H
