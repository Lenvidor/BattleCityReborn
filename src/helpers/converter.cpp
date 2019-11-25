#include "converter.h"

QPoint Converter::toVector(const Direction::Enum &value)
{
    int x = value == Direction::LEFT ? -1 : value == Direction::RIGHT ? 1 : 0;
    int y = value == Direction::UP ? -1 : value == Direction::DOWN ? 1 : 0;
    return QPoint(x,y);
}

QPointF Converter::toVectorF(const Direction::Enum &value)
{
    return toVector(value);
}

QPoint Converter::toPoint(const QPointF &value)
{
    return QPoint(qFloor(value.x()),qFloor(value.y()));
}
