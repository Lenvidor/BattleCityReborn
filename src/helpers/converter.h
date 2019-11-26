#pragma once

#include "../enums/direction.h"
#include <QtMath>
#include <QPoint>
#include <QPointF>

class Converter
{
public:
    static QPoint toVector(const Direction::Enum &value);
    static QPointF toVectorF(const Direction::Enum &value);
    static QPoint toPoint(const QPointF &value);
};
