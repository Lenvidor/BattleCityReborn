#include "eagle.h"

void Eagle::defeat()
{
    if (!mDefeated)
    {
        mDefeated = true;
        emit defeatedChanged();
    }
}

bool Eagle::defeated()
{
    return mDefeated;
}
