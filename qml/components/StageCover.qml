import QtQuick 2.0
import "../basic"

Item {
    id: main
    anchors.fill: parent
    property int delay: 500;
    property int stageNumber: 0;
    property bool contentShowed: false;

    Rectangle {
        id: topBorderContainer
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: contentShowed ? 0 : Math.floor(main.height/2)

        GrayPlaceholder {
            id: topBorder

            transform: Scale {
                xScale: topBorderContainer.width/topBorder.width
                yScale: topBorderContainer.height/topBorder.height
            }
        }

        Behavior on height {
            NumberAnimation {
                duration: delay
                easing.type: Easing.Linear
            }
        }
    }


    Rectangle {
        id: bottomBorderContainer
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: contentShowed ? 0 : Math.ceil(main.height/2)

        GrayPlaceholder {
            id: bottomBorder

            transform: Scale {
                xScale: bottomBorderContainer.width/bottomBorder.width
                yScale: bottomBorderContainer.height/bottomBorder.height
            }
        }

        Behavior on height {
            NumberAnimation {
                duration: delay
                easing.type: Easing.Linear
            }
        }
    }

    Rectangle{
        visible: !contentShowed
        anchors.centerIn: parent
        width: 5*8
        height: 8
        color: "black"

        ImageModel {
            id: stageString
            xRw: 20*16+8
            yRw: 11*16
            width: 5*8
            height: 8
        }
        TwoDigitNumber {
            number: stageNumber
            anchors.left: stageString.right
        }
    }


    function showContent() {
        delay = 500;
        contentShowed = true;
    }

    function hideContent() {
        delay = 0;
        contentShowed = false;
    }
}
