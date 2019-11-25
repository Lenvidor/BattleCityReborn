#ifndef TILE_H
#define TILE_H

#include <QGenericMatrix>
#include <QtMath>
#include "../interactiveobject.h"
#include "../../enums/tileorientation.h"
#include "../../enums/tiletype.h"
#include "../../constants/definedconstants.h"

class Tile : public InteractiveObject
{
    Q_OBJECT
public:
    Tile();

    Q_PROPERTY(TileOrientation::Enum orientation READ orientation NOTIFY orientationChanged)
    Q_PROPERTY(TileType::Enum type READ type NOTIFY typeChanged)

    Q_SLOT bool get(int i, int j);

    virtual bool intersects(const QRect &rect) const override;
    virtual void destruct(const QRect &rect);

    TileOrientation::Enum orientation() const;
    void setOrientation(const TileOrientation::Enum &value);

    TileType::Enum type() const;
    void setType(const TileType::Enum &value);

signals:
    void tileMapChanged();
    void typeChanged();
    void orientationChanged();

private slots:
    void onOrientationChanged();
    void onTypeChanged();

private:
    QGenericMatrix<TILE_MAP_SIZE,TILE_MAP_SIZE,bool> mTileMap;
    TileOrientation::Enum mOrientation {TileOrientation::NONE};
    TileType::Enum mType {TileType::BRICK_TILE};

    QRect convertToIntersectedQuantors(const QRect &rect) const;
    bool checkIntersection(const QRect &rect) const;
    void updateTileMap(const QRect &rect, bool value);
    void refreshTileMap();
    void checkTileExisting();
};

Q_DECLARE_METATYPE(Tile *)
typedef QSharedPointer<Tile> STile;

#endif // TILE_H
