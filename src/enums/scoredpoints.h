#ifndef SCOREDPOINTS_H
#define SCOREDPOINTS_H

#include <QObject>

class ScoredPoints : public QObject
{
    Q_OBJECT
    Q_ENUMS(Enum)

public:
    enum Enum : unsigned int {
        MIN = 0,
        ONE_HUNDRED = 0,
        TWO_HUNDREDS = 1,
        THREE_HUNDREDS = 2,
        FOUR_HUNDREDS = 3,
        FIVE_HUNDREDS = 4,
        NONE = 5,
        MAX = 5
    };

    static bool isValid(Enum value)
    {
        return MIN <= value && value <= MAX;
    }
};

#endif // SCOREDPOINTS_H
