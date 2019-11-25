import QtQuick 2.5
import QtQuick.Window 2.2
import MyControllers 1.0
import "qml"

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Battle City")

    Game {
        id: myGame
    }

    GameView {
        id: mainItem
        width: 16*16
        height: 15*16
        focus: true
        game: myGame

        transform: Scale {
            xScale: window.width/mainItem.width;
            yScale: window.height/mainItem.height;
        }
    }
}
