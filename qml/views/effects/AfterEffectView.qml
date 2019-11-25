import QtQuick 2.0
import MyEnums 1.0

Item {
    id: afterEffect
    z: Z.AFTER_EFFECT

    property int scoredPoints
    property int explosionType

    Explosion {
        id: explosionModel
        visible: afterEffect.explosionType != ExplosionType.NONE
        explosionType: afterEffect.explosionType
        onFullCycleObtained: {
            if (afterEffect.scoredPoints != ScoredPoints.NONE)
            {
                visible = false;
                scoredPointsModel.visible = true;
            }
            else
            {
                afterEffect.destroy();
            }
        }
    }

    ScorePoints {
        id: scoredPointsModel
        scoredPoints: afterEffect.scoredPoints
        visible: afterEffect.explosionType == ExplosionType.NONE
                 && afterEffect.scoredPoints != ScoredPoints.NONE;
        onFullCycleObtained: {
            afterEffect.destroy();
        }
    }
}
