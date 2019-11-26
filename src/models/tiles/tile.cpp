#include "tile.h"

Tile::Tile()
{
    refreshTileMap();
    QObject::connect(this,&Tile::orientationChanged,this,&Tile::onOrientationChanged);
    QObject::connect(this,&Tile::typeChanged,this,&Tile::onTypeChanged);
}

bool Tile::get(int i, int j)
{
    if (i < 0 || j < 0 || i >= TILE_MAP_SIZE || j >= TILE_MAP_SIZE)
        return false;

    return mTileMap(j,i);
}

bool Tile::intersects(const QRect &rect) const
{
    if (InteractiveObject::intersects(rect))
    {
        return checkIntersection(convertToIntersectedQuantors(rect));
    }
    return false;
}

void Tile::destruct(const QRect &rect)
{
    if (intersects(rect))
    {
        updateTileMap(convertToIntersectedQuantors(rect),false);
        emit tileMapChanged();
        checkTileExisting();
    }
}

TileOrientation::Enum Tile::orientation() const
{
    return mOrientation;
}

void Tile::setOrientation(const TileOrientation::Enum &value)
{
    if (TileOrientation::isValid(value) && mOrientation != value)
    {
        mOrientation = value;
        emit orientationChanged();
    }
}

void Tile::onOrientationChanged()
{
    refreshTileMap();
}

void Tile::onTypeChanged()
{
    refreshTileMap();
}

TileType::Enum Tile::type() const
{
    return mType;
}

void Tile::setType(const TileType::Enum &value)
{
    if (TileType::isValid(value) && mType != value)
    {
        mType = value;
        emit typeChanged();
    }
}

bool Tile::checkIntersection(const QRect &rect) const
{
    bool interacts = false;

    for (int i = rect.top(); i <= rect.bottom(); i++)
    {
        for (int j = rect.left(); j <= rect.right(); j++)
        {
            interacts |= mTileMap(i,j);
        }
    }

    return interacts;
}

void Tile::updateTileMap(const QRect &rect, bool value)
{
    for (int i = rect.top(); i <= rect.bottom(); i++)
    {
        for (int j = rect.left(); j <= rect.right(); j++)
        {
            mTileMap(i,j) = value;
        }
    }
}

void Tile::refreshTileMap()
{
    updateTileMap(QRect(QPoint(0,0),QSize(TILE_MAP_SIZE,TILE_MAP_SIZE)),false);

    int left = mOrientation & TileOrientation::RIGHT ? HALF_TILE_MAP : 0;
    int right = mOrientation & TileOrientation::LEFT ? HALF_TILE_MAP - 1 : TILE_MAP_SIZE - 1;
    int top = mOrientation & TileOrientation::BOTTOM ? HALF_TILE_MAP : 0;
    int bottom = mOrientation & TileOrientation::TOP ? HALF_TILE_MAP - 1 : TILE_MAP_SIZE - 1;

    updateTileMap(QRect(QPoint(left,top),QPoint(right,bottom)),true);

    emit tileMapChanged();
}

void Tile::checkTileExisting()
{
    bool exists = false;

    for (int i = 0; i < TILE_MAP_SIZE; i++)
    {
        for (int j = 0; j < TILE_MAP_SIZE; j++)
        {
            exists |= mTileMap(i,j);
        }
    }

    if (!exists)
    {
        terminate();
    }
}

QRect Tile::convertToIntersectedQuantors(const QRect &rect) const
{
    QRect intersected = this->rect().intersected(rect);

    intersected.moveTopLeft(intersected.topLeft() - this->rect().topLeft());

    int left = intersected.left()/TILE_MAP_SIZE;
    int right = intersected.right()/TILE_MAP_SIZE;
    int top = intersected.top()/TILE_MAP_SIZE;
    int bottom = intersected.bottom()/TILE_MAP_SIZE;

    return QRect(QRect(QPoint(left,top),QPoint(right,bottom)));
}
