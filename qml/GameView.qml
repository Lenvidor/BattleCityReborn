import QtQuick 2.0
import MyControllers 1.0
import MyEnums 1.0
import "components"

Item {
    id: gameView
    property Game game

    Timer {
        id: timer
        interval: 100; running: true; repeat: true
    }

    signal screenStateProposed(int screenState);

    ContourBorder { borderWidth: 16 }

    InfoPanel {
        id: border
        tanksAvailable: game.stageInfo.tanksAvailable
        playerLives: game.playerInfo.lives
        anchors.right: parent.right
    }

    Rectangle {
        id: gameArea
        anchors.fill: parent
        anchors.margins: 16
        anchors.rightMargin: 32
        color: "black"

        GameContent {
            id: content
            anchors.fill: parent
            timer: game.paused ? null : timer
            objects: game.modelsContainer
        }

        PauseLabel {
            anchors.centerIn: parent
            timer: timer
            paused: game.paused
        }

        GameOverLabel {
            id: gameOverLabel
            property int delay: visible ? 1000 : 0;
            anchors.horizontalCenter: parent.horizontalCenter
            y: visible ? parent.height/2 : parent.height;
            visible: game.over

            Behavior on y {
                NumberAnimation {
                    duration: gameOverLabel.delay
                    easing.type: Easing.Linear
                }
            }
        }
    }

    StageCover { id: cover; stageNumber: game.stageInfo.stageNumber }

    Connections {
        target: game
        onStartedChanged: {
            if (game.started) {
                cover.showContent();
            } else {
                cover.hideContent();
                game.unprepare();
                game.prepare();
            }
        }
        onOverChanged: {
            if (game.over)
            {
                game.stopMoving();
            }
        }
    }

    QtObject {
        id: keys
        property bool a: false
        property bool w: false
        property bool s: false
        property bool d: false
    }

    Keys.onReleased: {
        if (event.isAutoRepeat)
            return;

        switch (event.key)
        {
        case Qt.Key_W:
            keys.w = false;
            break;
        case Qt.Key_S:
            keys.s = false;
            break;
        case Qt.Key_A:
            keys.a = false;
            break;
        case Qt.Key_D:
            keys.d = false;
            break;
        }

        if (!keys.a && !keys.w && !keys.s && !keys.d)
        {
            game.stopMoving();
        }
    }

    Component.onCompleted: {
        game.prepare();
    }

    Keys.onPressed: {

        if (!game.ready || game.over)
            return;

        switch (event.key)
        {
        case Qt.Key_H:
            if (!game.started) {
                game.start();
            }

            if (game.paused) {
                game.unpause();
            } else {
                game.pause();
            }
            break;
        case Qt.Key_Escape:
            if (game.started)
            {
                game.finish();
            }
            else
            {
                Qt.quit();
            }

            break;
        }

        if (!game.paused)
        {
            switch (event.key)
            {
            case Qt.Key_1:
                game.upgradePlayer();
                break;
            case Qt.Key_2:
                game.randomPowerUp();
                break;
            case Qt.Key_3:
                game.destroyPlayerTank();
                break;
            case Qt.Key_4:
                game.addEnemyPlayer();
                break;
            case Qt.Key_W:
                keys.w = true;
                game.movePlayer(Direction.UP);
                break;
            case Qt.Key_S:
                keys.s = true;
                game.movePlayer(Direction.DOWN);
                break;
            case Qt.Key_A:
                keys.a = true;
                game.movePlayer(Direction.LEFT);
                break;
            case Qt.Key_D:
                keys.d = true;
                game.movePlayer(Direction.RIGHT);
                break;
            case Qt.Key_J:
                if (!event.isAutoRepeat)
                {
                    game.fireFromPlayer();
                }
                break;
            }
        }
    }
}
