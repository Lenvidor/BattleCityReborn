#pragma once

#include <QObject>

class PowerUpType : public QObject
{
    Q_OBJECT
    Q_ENUMS(Enum)
public:
    enum Enum : int
    {
        MIN = 0,
        HELMET = 0,
        CLOCK = 1,
        SHOVEL = 2,
        STAR = 3,
        SHELL = 4,
        TANK = 5,
        MAX = 5
    };

    static bool isValid(Enum value)
    {
        return MIN <= value && value <= MAX;
    }
};
