#include <nds.h>
#include "entity.h"

Entity::Entity(const u8 *SpriteData) {
  c_BGPixels.x = 0;
  c_BGPixels.y = 0;
  c_BGTiles.x  = 0;
  c_BGTiles.y  = 0;

  pSpriteBase = oamAllocateGfx(&oamMain, SpriteSize_16x32, SpriteColorFormat_256Color);
  memcpy(pSpriteBase, SpriteData, 256*2);
}

void Entity::oamSetEntity(int index, int X, int Y, bool Hide)
{
  oamSet(&oamMain, index, X, Y,
         1, //priority
         0, //palette index for multiple palettes
         SpriteSize_16x32,
         SpriteColorFormat_256Color,
         pSpriteBase, //pointer to loaded graphics
         0,  //rot/scale matrix index
         false, //double size when rot/scale?
         Hide, //hide sprite?
         false, false, //vflip, hflip?
         false  //mosiac?
         );
}

