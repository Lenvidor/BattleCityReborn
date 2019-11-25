#ifndef TILETYPE_H
#define TILETYPE_H

#include <QObject>

class TileType : public QObject
{
    Q_OBJECT
    Q_ENUMS(Enum)
public:
    enum Enum : int
    {
        MIN = 0,
        NONE = 0,
        BRICK_TILE = 1,
        CONCRETE_TILE = 2,
        MAX = 2
    };

    static bool isValid(Enum value)
    {
        return MIN <= value && value <= MAX;
    }
};

#endif // TILETYPE_H
