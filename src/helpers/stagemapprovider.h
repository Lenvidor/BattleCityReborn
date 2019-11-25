#ifndef STAGEMAPPROVIDER_H
#define STAGEMAPPROVIDER_H

#include <QSharedPointer>
#include <QGenericMatrix>
#include "../constants/definedconstants.h"
#include "../enums/tileorientation.h"
#include "../enums/tiletype.h"

typedef QGenericMatrix<STAGE_MAP_SIZE,STAGE_MAP_SIZE,int> StageMap;

class StageMapProvider
{
public:
    StageMapProvider();
    const StageMap getStageMap();

private:
    int stage1[STAGE_MAP_SIZE*STAGE_MAP_SIZE] {};
};

typedef QSharedPointer<StageMapProvider> SStageMapProvider;

#endif // STAGEMAPPROVIDER_H
