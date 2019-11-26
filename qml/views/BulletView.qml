import QtQuick 2.0
import MyEnums 1.0
import MyModels 1.0
import "../basic"

BaseView {
    id: main
    z: Z.BULLET

    QtObject {
        id: member
        property Bullet object: main.object
    }

    ImageModel {
        x: (member.object && member.object.direction == Direction.UP ? -1 : 0)
        y: (member.object && member.object.direction == Direction.RIGHT ? -1 : 0)
        visible: member.object
        xRw: member.object ? (member.object.direction + 16) * 16 : 0
        yRw: 13*16
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
