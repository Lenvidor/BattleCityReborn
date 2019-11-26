#include "stageinfo.h"

int StageInfo::stageNumber() const
{
    return mStageNumber;
}

void StageInfo::setStageNumber(int value)
{
    if (mStageNumber != value)
    {
        mStageNumber = value;
        emit stageNumberChanged();
    }
}

int StageInfo::tanksAvailable() const
{
    return mTanksAvailable;
}

void StageInfo::setTanksAvailable(int value)
{
    if (mTanksAvailable != value)
    {
        mTanksAvailable = value;
        emit tanksAvailableChanged();
    }
}
