import QtQuick 2.0
import MyContainers 1.0
import "../helpers"

Item {
    id: gameContent
    objectName: "gameContent"
    anchors.fill: parent

    property Timer timer
    property ModelsContainer objects
    property int childrenCounter: 0

    QtObject {
        id: innerGameContent;
        property Timer timer: gameContent.visible ? gameContent.timer : null
    }

    InstanceOf { id: instance }

    Connections {
        target: objects
        onObjectInserted: {
            var object = obj;
            createModel(obj)
        }
    }

    function createModel(obj)
    {
        var object = obj;

        var component;

        if (instance.is("PlayerTank", object)) {
            component = Qt.createComponent("../views/PlayerTankView.qml");
        } else if (instance.is("EnemyTank", object)) {
            component = Qt.createComponent("../views/EnemyTankView.qml");
        } else if (instance.is("PowerUp", object)) {
            component = Qt.createComponent("../views/PowerUpView.qml");
        } else if (instance.is("Eagle", object)) {
            component = Qt.createComponent("../views/EagleView.qml");
        } else if (instance.is("Tile", object)) {
            component = Qt.createComponent("../views/TileView.qml");
        } else if (instance.is("Bullet", object)) {
            component = Qt.createComponent("../views/BulletView.qml");
        }

        component.createObject(gameContent, {"object": object });
    }

    function createAfterEffect(obj)
    {
        var component = Qt.createComponent("../views/effects/AfterEffectView.qml");
        component.createObject(gameContent, obj);
    }
}
