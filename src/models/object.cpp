#include "object.h"

Object::Object(QObject *parent) : QObject(parent)
{
}

int Object::x() const
{
    return mPosition.x();
}

int Object::y() const
{
    return mPosition.y();
}

int Object::width() const
{
    return mSize.width();
}

int Object::height() const
{
    return mSize.height();
}

int Object::top() const
{
    return rect().top();
}

int Object::bottom() const
{
    return rect().bottom();
}

int Object::left() const
{
    return rect().left();
}

int Object::right() const
{
    return rect().right();
}

QPoint Object::position() const
{
    return mPosition;
}

void Object::setPosition(const QPoint &position)
{
    if (mPosition != position)
    {
        mPosition = position;
        emit positionChanged();
    }
}

QSize Object::size() const
{
    return mSize;
}

void Object::setSize(const QSize &size)
{
    if (mSize != size)
    {
        mSize = size;
        emit sizeChanged();
    }
}

QRect Object::rect() const
{
    QRect result = QRect(QPoint(),mSize);
    result.moveCenter(mPosition);
    return result;
}
