import QtQuick 2.0
import "../basic"

Item {

    id: infoPanelItem
    property int tanksAvailable: 0
    property int playerLives: 0

    width: 16*2;
    height: 16*15;

    ImageModel {
        id: panelBackground
        xRw: 23*16;
        yRw: 0;
        width: 16*2;
        height: 16*15;
    }

    Grid {
        id: tanksAvailabilityGrid
        rows: 10
        columns: 2

        x: 8
        y: 8*3

        Repeater {

            model: 20
            Item {
                width: 8
                height: 8
                GrayPlaceholder { visible: index >= infoPanelItem.tanksAvailable }
                ImageModel {
                    visible: index < infoPanelItem.tanksAvailable;
                    xRw: 20*16
                    yRw: 12*16
                    width: 8
                    height: 8
                }
            }
        }
    }

    Digit {
        y: 9*16
        x: 16
        digit: infoPanelItem.playerLives
    }

    GrayPlaceholder {
        y: 10*16
        x: 8
        width: 16
        height: 16
    }

    TwoDigitNumber {
        y: 12*16+8
        x: 8
        number: 1
    }
}
