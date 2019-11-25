import QtQuick 2.0

Item {
    property int xRw: 0
    property int yRw: 0

    width: 16
    height: 16
    clip: true

    Image {
        x: -xRw
        y: -yRw
        fillMode: Image.Pad
        verticalAlignment: Image.AlignTop
        horizontalAlignment: Image.AlignLeft
        smooth: false
        source: "qrc:/qml/images/model.png"
    }
}
