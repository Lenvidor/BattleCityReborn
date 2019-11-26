#pragma once

#include <QObject>

class ExplosionType : public QObject
{
    Q_OBJECT
    Q_ENUMS(Enum)

public:
    enum Enum : unsigned int
    {
        MIN = 0,
        BULLET_EXPLOSION = 0,
        TANK_EXPLOSION = 1,
        NONE = 2,
        MAX = 2
    };

    static bool isValid(Enum value)
    {
        return MIN <= value && value <= MAX;
    }
};
