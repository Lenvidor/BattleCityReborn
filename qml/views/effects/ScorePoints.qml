import QtQuick 2.0
import MyEnums 1.0
import "../../basic"

BaseEffect {
    id: main
    property int scoredPoints: ScoredPoints.NONE

    QtObject {
        id: member
        property int frameNumber: 0
        onFrameNumberChanged: {
            if (frameNumber == 5)
            {
                fullCycleObtained();
            }

            frameNumber %=5;
        }
    }

    ImageModel {
        xRw: (18 + scoredPoints) * 16;
        yRw: 10*16
    }

    Connections {
        target: inner.timer
        onTriggered: {
            member.frameNumber++;
        }
    }
}
