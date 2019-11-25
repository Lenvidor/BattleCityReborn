import QtQuick 2.0
import MyEnums 1.0
import MyModels 1.0
import "../basic"

BaseView {
    id:main
    z: Z.POWER_UP

    QtObject {
        id: member
        property PowerUp object: main.object
        property int frameNumber: 0
        onFrameNumberChanged: { frameNumber %= 6; }
    }

    ImageModel {
        visible: member.object && member.frameNumber < 3;
        xRw: member.object ? (16 + member.object.type) * 16 : 0;
        yRw: 7*16;
    }

    Connections {
        target: inner.timer
        onTriggered: { member.frameNumber++ }
    }
}
