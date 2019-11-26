#pragma once

#include <QObject>

class Direction : public QObject
{
    Q_OBJECT
    Q_ENUMS(Enum)
public:
    enum Enum : int
    {
        MIN = 0,
        UP = 0,
        LEFT = 1,
        DOWN = 2,
        RIGHT = 3,
        MAX = 3
    };

    static bool isValid(Enum value)
    {
        return MIN <= value && value <= MAX;
    }
};
