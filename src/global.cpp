#include "global.h"

QSharedPointer<Global> Global::mInstance = QSharedPointer<Global>(nullptr);

QSharedPointer<Global> Global::getInstance()
{
    if (!Global::mInstance)
    {
        Global::mInstance = QSharedPointer<Global>(new Global());
    }

    return Global::mInstance;
}

