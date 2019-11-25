#include "stagemapprovider.h"

#define N TileType::NONE
#define C TileType::CONCRETE_TILE
#define B TileType::BRICK_TILE
#define ON TileOrientation::NONE
#define UP TileOrientation::TOP
#define DN TileOrientation::BOTTOM
#define RT TileOrientation::RIGHT
#define LT TileOrientation::LEFT
#define UR TileOrientation::TOP_RIGHT_CORNER
#define UL TileOrientation::TOP_LEFT_CORNER
#define DR TileOrientation::BOTTOM_RIGHT_CORNER
#define DL TileOrientation::BOTTOM_LEFT_CORNER

#define SHIFT 4

#define O(a) ((int(a))<<SHIFT)
#define U(a) (((int(a))<<SHIFT)+int(UP))
#define D(a) (((int(a))<<SHIFT)+int(DN))
#define L(a) (((int(a))<<SHIFT)+int(LT))
#define R(a) (((int(a))<<SHIFT)+int(RT))
#define X(a) (((int(a))<<SHIFT)+int(DR))
#define Y(a) (((int(a))<<SHIFT)+int(DL))
#define S(a,b) (((int(a))<<SHIFT)+int(b))

#define NONE S(N,ON)

StageMapProvider::StageMapProvider()
    : stage1{
          NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
          NONE, O(B), NONE, O(B), NONE, O(B), NONE, O(B), NONE, O(B), NONE, O(B), NONE,
          NONE, O(B), NONE, O(B), NONE, O(B), NONE, O(B), NONE, O(B), NONE, O(B), NONE,
          NONE, O(B), NONE, O(B), NONE, O(B), O(C), O(B), NONE, O(B), NONE, O(B), NONE,
          NONE, O(B), NONE, O(B), NONE, U(B), NONE, U(B), NONE, O(B), NONE, O(B), NONE,
          NONE, U(B), NONE, U(B), NONE, D(B), NONE, D(B), NONE, U(B), NONE, U(B), NONE,
          D(B), NONE, D(B), D(B), NONE, U(B), NONE, U(B), NONE, D(B), D(B), NONE, D(B),
          U(C), NONE, U(B), U(B), NONE, D(B), NONE, D(B), NONE, U(B), U(B), NONE, U(C),
          NONE, D(B), NONE, D(B), NONE, O(B), O(B), O(B), NONE, D(B), NONE, D(B), NONE,
          NONE, O(B), NONE, O(B), NONE, O(B), NONE, O(B), NONE, O(B), NONE, O(B), NONE,
          NONE, O(B), NONE, O(B), NONE, U(B), NONE, U(B), NONE, O(B), NONE, O(B), NONE,
          NONE, O(B), NONE, O(B), NONE, X(B), D(B), Y(B), NONE, O(B), NONE, O(B), NONE,
          NONE, NONE, NONE, NONE, NONE, R(B), NONE, L(B), NONE, NONE, NONE, NONE, NONE
      }
{

}

const StageMap StageMapProvider::getStageMap()
{
    return StageMap(stage1);
}
