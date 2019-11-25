import QtQuick 2.0
import MyModels 1.0
import MyEnums 1.0

Item {
    id: main
    property InteractiveObject object
    property Timer timer: innerGameContent.timer
    x: main.object ? main.object.position.x : 0
    y: main.object ? main.object.position.y : 0

    property alias inner: interactiveInner

    QtObject {
        id: interactiveInner
        property Timer timer: main.visible ? main.timer : null
    }

    Connections{
        target: main.object
        onTerminatedChanged: {

            if (main.visible &&
                (main.object.explosionType != ExplosionType.NONE ||
                 main.object.scoredPoints != ScoredPoints.NONE))
            {
                var obj = {
                               "x":main.x,
                               "y":main.y,
                               "explosionType":object.explosionType,
                               "scoredPoints":object.scoredPoints
                           };
                createAfterEffect(obj);
            }
            main.destroy();
        }
    }

    onObjectChanged: {
        if (!object)
        {
            main.destroy();
        }
    }
}
