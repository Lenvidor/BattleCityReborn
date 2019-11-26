import QtQuick 2.0

Item {

    width: 16
    height: 8

    property int number: 0

    GrayPlaceholder {
        visible: number < 10
        x: 0
        y: 0
    }

    Digit {
        visible: number >= 10
        digit: Math.floor(number/10);
        x: 0
        y: 0
    }
    Digit {
        digit: number % 10
        x: 8
        y: 0
    }

    onNumberChanged: {
        if (number < 0)
        {
            number = 0;
        }
        else if (number > 99)
        {
            number = 99;
        }
    }
}
