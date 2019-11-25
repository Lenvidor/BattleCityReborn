import QtQuick 2.0
import MyModels 1.0
import MyEnums 1.0
import "../basic"

BaseView {
    id: main
    z: Z.EAGLE

    QtObject {
        id: member
        property Eagle object: main.object
    }

    ImageModel {
        visible: member.object
        xRw: member.object ? member.object.defeated ? 20*16 : 19*16 : 0
        yRw: 2*16
    }
}
