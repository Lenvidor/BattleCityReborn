#include "playerinfo.h"

int PlayerInfo::lives() const
{
    return mLives;
}

void PlayerInfo::setLives(int values)
{
    if (mLives != values)
    {
        mLives = values;
        emit livesChanged();
    }
}

int PlayerInfo::score() const
{
    return mScore;
}

void PlayerInfo::setScore(int value)
{
    if (mScore != value)
    {
        mScore = value;
        emit scoreChanged();
    }
}
