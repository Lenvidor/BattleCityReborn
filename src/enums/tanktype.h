#pragma once

#include <QObject>

class TankType : public QObject
{
    Q_OBJECT
    Q_ENUMS(Enum)
public:
    enum Enum : int
    {
        MIN = 0,
        SIMPLE_TANK = 0,
        MOTOR_TANK = 1,
        RAPID_FIRE_TANK = 2,
        HEAVY_TANK = 3,
        MAX = 3
    };

    static bool isValid(Enum value)
    {
        return MIN <= value && value <= MAX;
    }
};
