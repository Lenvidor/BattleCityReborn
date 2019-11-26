import QtQuick 2.0
import MyEnums 1.0
import MyModels 1.0
import "../basic"

BaseView {
    id: main
    z: Z.TANK

    QtObject {
        id: member
        property EnemyTank object: main.object
        property int appearFrameNumber: 0
        property int tankFrameNumber: 0
        property int bonusFrameNumber: 0
        property int baseX: {
            if (!member.object)
                return 0;

            var x = 0;

            switch (member.object.hitPoints)
            {
            case 1:
            case 4:
                x = 16*8;
                break;
            case 2:
            case 3:
                x = 0;
                break;
            }

            return x;
        }
        property int baseY: {
            if (!member.object)
                return 0;

            var y = 0;

            switch (member.object.hitPoints)
            {
            case 1:
            case 4:
            case 3:
                y = 0;
                break;
            case 2:
                y = 16*8;
                break;
            }

            return y;
        }

        onTankFrameNumberChanged: { tankFrameNumber %= 2 }
        onBonusFrameNumberChanged: { bonusFrameNumber %= 4 }
        onAppearFrameNumberChanged: { member.appearFrameNumber %= 6 }
    }

    ImageModel {
        id: apperImageModel
        visible: member.object && member.object.aboutToAppear
        yRw: 6*16
        xRw: 16 * (16 + Math.abs(( member.appearFrameNumber >= 4 ? -6 : 0 ) + member.appearFrameNumber))
    }

    ImageModel {
        visible: member.object && !member.object.aboutToAppear
        xRw: {
            if (!member.object)
                return 0;

            var x = member.object.bonus && member.bonusFrameNumber < 2 ? 16*8 : member.baseX;

            return x + 16 * ( 2 * member.object.direction + member.tankFrameNumber );
        }
        yRw: {
            if (!member.object)
                return 0;

            var y = member.object.bonus && member.bonusFrameNumber < 2 ? 16*8 : member.baseY;

            return y + 16 * (member.object.type + 4);
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

    Connections {
        target: inner.timer
        onTriggered: {
            if (!member.object)
                return;

            if (member.object.moving)
            {
                member.tankFrameNumber++;
            }
            if (member.object.bonus)
            {
                member.bonusFrameNumber++;
            }
            if (member.object.aboutToAppear)
            {
                member.appearFrameNumber++;
            }
        }
    }
}
