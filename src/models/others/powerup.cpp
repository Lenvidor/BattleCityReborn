#include "powerup.h"

PowerUpType::Enum PowerUp::type() const
{
    return mType;
}

void PowerUp::setType(const PowerUpType::Enum &value)
{
    if (PowerUpType::isValid(value) && mType != value)
    {
        mType = value;
        emit typeChanged();
    }
}
