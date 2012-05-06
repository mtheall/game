#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <nds.h>
#include "struct.h"

class Entity{
private:
protected:
  u16 *pSpriteBase;
  vector2_t c_BGPixels;
  vector2_t c_BGTiles;
public:
  Entity(const u8 *SpriteData);

  void oamSetEntity(int Index, int X, int Y, bool Hide);

  const vector2_t getBGPixels() const { return c_BGPixels; }
  const vector2_t getBGTiles()  const { return c_BGTiles; }
};

#endif

