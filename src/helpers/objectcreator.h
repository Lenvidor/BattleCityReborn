#ifndef OBJECTCREATOR_H
#define OBJECTCREATOR_H

#include <QSharedPointer>
#include "../models/bullets/bullet.h"
#include "../models/tanks/enemytank.h"
#include "../models/tanks/playertank.h"
#include "../models/others/eagle.h"
#include "../models/others/powerup.h"
#include "../models/tiles/tile.h"
#include "../constants/modelsproperties.h"

class ObjectCreator
{
public:
    STile createTile(int i, int j, TileType::Enum type, TileOrientation::Enum orientation);
    SEnemyTank createEnemyTank(int i, int j, TankType::Enum type);
    SPowerUp createPowerUp(int i, int j, PowerUpType::Enum type);
    SPlayerTank createPlayerTank(int playerNumber = 0);
    SEagle createEagle();
    SBullet createBullet(STank tank);
};

typedef QSharedPointer<ObjectCreator> SObjectCreator;

#endif // OBJECTCREATOR_H
