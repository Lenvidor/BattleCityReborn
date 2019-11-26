#pragma once

#include <QtQml>

#include "game.h"
#include "models/bullets/bullet.h"
#include "models/others/eagle.h"
#include "models/others/powerup.h"
#include "models/tanks/enemytank.h"
#include "models/tanks/playertank.h"
#include "models/tiles/tile.h"
#include "containers/modelscontainer.h"
#include "metadata/playerinfo.h"
#include "metadata/stageinfo.h"
#include "enums/direction.h"
#include "enums/poweruptype.h"
#include "enums/tileorientation.h"
#include "enums/tiletype.h"
#include "enums/tanktype.h"
#include "enums/explosiontype.h"
#include "enums/scoredpoints.h"
#include "enums/z.h"

class Registrar
{
public:
    static void registerQMLTypes();
};
