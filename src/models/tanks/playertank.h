#pragma once

#include "tank.h"

class PlayerTank : public Tank
{
    Q_OBJECT
public:
    Q_PROPERTY(int numberOfStars READ numberOfStars NOTIFY numberOfStarsChanged)
    Q_PROPERTY(int playerNumber READ playerNumber NOTIFY playerNumberChanged)
    Q_PROPERTY(bool invulnerable READ invulnerable NOTIFY invulnerableChanged)

    int numberOfStars() const;
    void setNumberOfStars(int numberOfStars);

    int playerNumber() const;
    void setPlayerNumber(int playerNumber);

    bool invulnerable() const;
    void setInvulnerable(bool invulnerable);

public slots:
    void makeVulnerable();

signals:
    void numberOfStarsChanged();
    void playerNumberChanged();
    void invulnerableChanged();

private:
    int mNumberOfStars;
    int mPlayerNumber;
    bool mInvulnerable;
};

Q_DECLARE_METATYPE(PlayerTank *)
typedef QSharedPointer<PlayerTank> SPlayerTank;
