#ifndef Z_H
#define Z_H

#include <QObject>

class Z : public QObject
{
    Q_OBJECT
    Q_ENUMS(Enum)
public:
    enum Enum : int
    {
        MIN = 0,
        DEFAULT = 0,
        TILE = 0,
        EAGLE = 0,
        BULLET = 1,
        TANK = 2,
        EXPLOSION = 3,
        AFTER_EFFECT = 3,
        POWER_UP = 4,
        MAX = 4
    };

    static bool isValid(Enum value)
    {
        return MIN <= value && value <= MAX;
    }
};

#endif // Z_H
