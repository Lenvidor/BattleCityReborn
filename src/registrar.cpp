#include "registrar.h"

#define QML_NAME(a) #a

void Registrar::registerQMLTypes()
{
    qmlRegisterType<Game>("MyControllers",1,0,QML_NAME(Game));
    qmlRegisterType<ModelsContainer>("MyContainers",1,0,QML_NAME(ModelsContainer));

    qmlRegisterType<EnemyTank>("MyModels",1,0,QML_NAME(EnemyTank));
    qmlRegisterType<PlayerTank>("MyModels",1,0,QML_NAME(PlayerTank));
    qmlRegisterType<Bullet>("MyModels",1,0,QML_NAME(Bullet));
    qmlRegisterType<Eagle>("MyModels",1,0,QML_NAME(Eagle));
    qmlRegisterType<Tile>("MyModels",1,0,QML_NAME(Tile));
    qmlRegisterType<PowerUp>("MyModels",1,0,QML_NAME(PowerUp));
    qmlRegisterType<Tank>("MyModels",1,0,QML_NAME(Tank));
    qmlRegisterType<Object>("MyModels",1,0,QML_NAME(Object));
    qmlRegisterType<MovingObject>("MyModels",1,0,QML_NAME(MovingObject));
    qmlRegisterType<InteractiveObject>("MyModels",1,0,QML_NAME(InteractiveObject));

    qmlRegisterType<TankType>("MyEnums",1,0,QML_NAME(TankType));
    qmlRegisterType<TileType>("MyEnums",1,0,QML_NAME(TileType));
    qmlRegisterType<TileOrientation>("MyEnums",1,0,QML_NAME(TileOrientation));
    qmlRegisterType<Direction>("MyEnums",1,0,QML_NAME(Direction));
    qmlRegisterType<PowerUpType>("MyEnums",1,0,QML_NAME(PowerUpType));
    qmlRegisterType<ExplosionType>("MyEnums",1,0,QML_NAME(ExplosionType));
    qmlRegisterType<ScoredPoints>("MyEnums",1,0,QML_NAME(ScoredPoints));
    qmlRegisterType<Z>("MyEnums",1,0,QML_NAME(Z));

    qmlRegisterType<PlayerInfo>("MyMetadata",1,0,QML_NAME(PlayerInfo));
    qmlRegisterType<StageInfo>("MyMetadata",1,0,QML_NAME(StageInfo));
}
