#include "playertank.h"

int PlayerTank::numberOfStars() const
{
    return mNumberOfStars;
}

void PlayerTank::setNumberOfStars(int numberOfStars)
{
    if (mNumberOfStars != numberOfStars)
    {
        mNumberOfStars = numberOfStars;
        emit numberOfStarsChanged();
    }
}

int PlayerTank::playerNumber() const
{
    return mPlayerNumber;
}

void PlayerTank::setPlayerNumber(int playerNumber)
{
    if (mPlayerNumber != playerNumber)
    {
        mPlayerNumber = playerNumber;
        emit playerNumberChanged();
    }
}

bool PlayerTank::invulnerable() const
{
    return mInvulnerable;
}

void PlayerTank::setInvulnerable(bool invulnerable)
{
    if (mInvulnerable != invulnerable)
    {
        mInvulnerable = invulnerable;
        emit invulnerableChanged();
    }
}

void PlayerTank::makeVulnerable()
{
    setInvulnerable(false);
}
