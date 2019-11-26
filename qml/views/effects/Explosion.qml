import QtQuick 2.0
import MyEnums 1.0
import "../../basic"

BaseEffect {
    id: main

    property int explosionType: ExplosionType.NONE

    QtObject {
        id: member
        property int frameNumber: 0
        onFrameNumberChanged: {
            if (explosionType == ExplosionType.BULLET_EXPLOSION)
            {
                if (frameNumber == 3)
                {
                    fullCycleObtained();
                }

                frameNumber %= 3;
            }
            else if (explosionType == ExplosionType.TANK_EXPLOSION)
            {
                if (frameNumber == 5)
                {
                    fullCycleObtained();
                }

                frameNumber %= 5;
            }
            else if (explosionType == ExplosionType.NONE)
            {
                fullCycleObtained()
                frameNumber %= 1;
            }
        }
    }

    ImageModel {
        id: imageModel
        visible: explosionType != ExplosionType.NONE
        xRw: {
            if (member.frameNumber < 3)
            {
                return 16 * (16 + member.frameNumber);
            }
            else
            {
                return 16 * 19 + (member.frameNumber - 3) * 32
            }
        }
        yRw: 16 * 8;
        width: member.frameNumber < 3 ? 16 : 32
        height: member.frameNumber < 3 ? 16 : 32
        x: member.frameNumber < 3 ? 0 : -8;
        y: member.frameNumber < 3 ? 0 : -8;
    }

    onExplosionTypeChanged: {
        if (explosionType != ExplosionType.BULLET_EXPLOSION
                && explosionType != ExplosionType.TANK_EXPLOSION)
        {
            explosionType = ExplosionType.NONE;
        }
    }

    Connections {
        target: inner.timer
        onTriggered: {
            member.frameNumber++;
        }
    }
}
