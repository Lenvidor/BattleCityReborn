import QtQuick 2.0
import MyModels 1.0
import MyEnums 1.0
import "../basic"

BaseView {
    id: main
    z: Z.TILE

    QtObject {
        id: member
        property Tile object: main.object
    }

    ImageModel {
        id: imageModel
        xRw: 16*16;
        yRw: member.object && member.object.type == TileType.CONCRETE_TILE ? 16 : 0;
    }

    Grid {
        id: grid
        rows: 4;
        columns: 4;
        Repeater {
            model: grid.rows*grid.columns
            Rectangle {
                id: item
                width: 4;
                height: 4;
                property int i: index % grid.columns;
                property int j: Math.floor(index/grid.columns);
                color: {
                    if (!member.object)
                        return "black";

                    return member.object.get(i,j) ? "transparent" : "black";
                }

                Connections {
                    target: member.object
                    onTileMapChanged: {
                        item.color = member.object.get(i,j) ? "transparent" : "black";
                    }
                }
            }
        }
    }
}
