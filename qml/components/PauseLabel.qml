import QtQuick 2.0
import "../basic"

Item {
    id: pauseLabel
    visible: paused && (frameNumber < 3)
    width: 5*8;
    height: 8;

    property Timer timer
    property bool paused: false
    property int frameNumber: 0

    QtObject {
        id: inner
        property Timer timer: paused ? pauseLabel.timer : null
    }

    ImageModel {
        xRw: 18*16
        yRw: 11*16
        width: 5*8
        height: 8
    }

    onPausedChanged: {
        if (paused)
        {
            frameNumber = 0;
        }
    }


    onFrameNumberChanged: { frameNumber %= 6 }

    Connections {
        target: inner.timer
        onTriggered: { frameNumber++ }
    }
}
