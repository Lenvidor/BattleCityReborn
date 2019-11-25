import QtQuick 2.0
import "../basic"

Item {
    property int borderWidth: 0
    anchors.fill: parent

    Rectangle {
        id: leftBorderContainer
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: borderWidth

        GrayPlaceholder {
            id: leftBorder

            transform: Scale {
                xScale: leftBorderContainer.width/leftBorder.width
                yScale: leftBorderContainer.height/leftBorder.height
            }
        }
    }

    Rectangle {
        id: rightBorderContainer
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: borderWidth

        GrayPlaceholder {
            id: rightBorder

            transform: Scale {
                xScale: rightBorderContainer.width/rightBorder.width
                yScale: rightBorderContainer.height/rightBorder.height
            }
        }
    }

    Rectangle {
        id: topBorderContainer
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: borderWidth

        GrayPlaceholder {
            id: topBorder

            transform: Scale {
                xScale: topBorderContainer.width/topBorder.width
                yScale: topBorderContainer.height/topBorder.height
            }
        }
    }

    Rectangle {
        id: bottomBorderContainer
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: borderWidth

        GrayPlaceholder {
            id: bottomBorder

            transform: Scale {
                xScale: bottomBorderContainer.width/bottomBorder.width
                yScale: bottomBorderContainer.height/bottomBorder.height
            }
        }
    }
}
