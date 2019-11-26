#pragma once

#include <QObject>

class TileOrientation : public QObject
{
    Q_OBJECT
    Q_ENUMS(Enum)

public:
    enum Enum : unsigned int
    {
        NONE = 0,
        BOTTOM = 1 << 0,
        TOP = 1 << 1,
        LEFT = 1 << 2,
        RIGHT = 1 << 3,

        TOP_LEFT_CORNER = TOP | LEFT,
        TOP_RIGHT_CORNER = TOP | RIGHT,
        BOTTOM_LEFT_CORNER = BOTTOM | LEFT,
        BOTTOM_RIGHT_CORNER = BOTTOM | RIGHT
    };

    static bool isValid(TileOrientation::Enum value)
    {
        switch (value)
        {
        case TileOrientation::NONE:
        case TileOrientation::BOTTOM:
        case TileOrientation::TOP:
        case TileOrientation::LEFT:
        case TileOrientation::RIGHT:
        case TileOrientation::TOP_LEFT_CORNER:
        case TileOrientation::TOP_RIGHT_CORNER:
        case TileOrientation::BOTTOM_LEFT_CORNER:
        case TileOrientation::BOTTOM_RIGHT_CORNER:
            return true;
        }

        return false;
    }
};
