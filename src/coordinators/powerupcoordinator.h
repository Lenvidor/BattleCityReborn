#ifndef POWERUPCOORDINATOR_H
#define POWERUPCOORDINATOR_H

#include <QObject>
#include "icoordinator.h"
#include "../global.h"

class PowerUpCoordinator : public QObject, public ICoordinator
{
    Q_OBJECT
public:
    PowerUpCoordinator();
    void initialize();
    void terminate();

    bool stopActionBonus() const;

private slots:
    void onPowerUpReached(PlayerTank *tank, PowerUp *powerUp);
    void onStopActionBonusFinished();
    void aboutToStopShovelBonus();
    void stopShovelBonus();
    void blinkShovelBonus();

private:
    SGlobal mGlobal;
    bool mStopActionBonus { false };
    bool mCurrentBrickBase { false };

    void processPowerUp(PlayerTank *tank, PowerUp *powerUp);
    void activateStopActionBonus();
    void activateShellBonus();
    void activateTankBonus();
    void activateShovelBonus();
    void finishStopActionBonus();
    void activateStarBonus(PlayerTank *tank);
    void activateHelmetBonus(PlayerTank *tank);
};

typedef QSharedPointer<PowerUpCoordinator> SPowerUpCoordinator;

#endif // POWERUPCOORDINATOR_H
