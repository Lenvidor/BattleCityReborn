import QtQuick 2.0
import MyModels 1.0

Item {
    id: item

    property PlayerTank         __PlayerTank
    property EnemyTank          __EnemyTank
    property Object             __Object
    property InteractiveObject  __InteractiveObject
    property MovingObject       __MovingObject
    property Tank               __Tank
    property Bullet             __Bullet
    property Tile               __Tile
    property PowerUp            __PowerUp
    property Eagle              __Eagle

    function is(typestring, object)
    {
        try {
            item["__"+typestring] = object;
            item["__"+typestring] = null;
            return true;
        } catch(error) {
            return false;
        }
    }
}
