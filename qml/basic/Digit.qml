import QtQuick 2.0

ImageModel {
    property int digit: 0
    xRw: 20*16 + (1 + digit%5 ) * 8;
    yRw: 11*16 + (1 + Math.floor(digit/5)) * 8;
    width: 8
    height: 8

    onDigitChanged: {
        if (digit < 0)
        {
            digit = 0;
        }
        else if (digit > 9)
        {
            digit = 9;
        }
    }
}
