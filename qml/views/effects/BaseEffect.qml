import QtQuick 2.0

Item {
    id: baseEffect
    property Timer timer: innerGameContent.timer
    property alias inner: innerEffect

    signal fullCycleObtained();


    QtObject {
        id: innerEffect
        property Timer timer: baseEffect.visible ? baseEffect.timer : null
    }
}
