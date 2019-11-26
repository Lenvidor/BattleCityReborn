#include "enemytank.h"


TankType::Enum EnemyTank::type() const
{
    return mType;
}

void EnemyTank::setType(const TankType::Enum &value)
{
    if (TankType::isValid(value) && mType != value)
    {
        mType = value;
        emit typeChanged();
    }
}

bool EnemyTank::bonus() const
{
    return mBonus;
}

void EnemyTank::setBonus(bool value)
{
    if (mBonus != value)
    {
        mBonus = value;
        emit bonusChanged();
    }
}
