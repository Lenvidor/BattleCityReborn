import QtQuick 2.0
import MyEnums 1.0
import MyModels 1.0
import "../basic"

BaseView {
    id: main
    z: Z.TANK

    QtObject {
        id: member
        property int appearFrameNumber: 0
        property int tankFrameNumber: 0
        property int invFrameNumber : 0
        property PlayerTank object: main.object

        onTankFrameNumberChanged: { member.tankFrameNumber %= 2 }
        onInvFrameNumberChanged: { member.invFrameNumber %= 2 }
        onAppearFrameNumberChanged: { member.appearFrameNumber %= 6 }
    }

    ImageModel {
        id: apperImageModel
        visible: member.object && member.object.aboutToAppear
        yRw: 6*16
        xRw: 16 * (16 + Math.abs(( member.appearFrameNumber >= 4 ? -6 : 0 ) + member.appearFrameNumber))
    }

    ImageModel {
        id: tankImageModel
        visible: member.object && !member.object.aboutToAppear
        yRw: member.object ? member.object.playerNumber * 16 * 8 + object.numberOfStars * 16 : 0
        xRw: member.object ? member.object.direction * 16 * 2 + member.tankFrameNumber * 16 : 0
    }

    ImageModel {
        id: invImageModel
        visible: member.object && member.object.invulnerable && !member.object.aboutToAppear
        yRw: 16 * 9
        xRw: 16 * 16 + member.invFrameNumber * 16
    }

    Connections{
        target: inner.timer
        onTriggered: {
            if (member.object && member.object.moving)
            {
                member.tankFrameNumber++;
            }
            if (object && object.invulnerable)
            {
                member.invFrameNumber++;
            }
            if (object && object.aboutToAppear)
            {
                member.appearFrameNumber++;
            }
        }
    }

    Behavior on x {
        NumberAnimation {
            duration: 50
            easing.type: Easing.Linear
        }
    }
    Behavior on y {
        NumberAnimation {
            duration: 50
            easing.type: Easing.Linear
        }
    }
}
