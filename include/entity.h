#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <nds.h>
#include "struct.h"

class Entity{
	private:
	protected:
		u16 *pSpriteBase;
		vector2_t c_BGPixels, c_BGTiles;
	public:
		void oamSetEntity(int Index, int X, int Y, bool Hide);	
		
		Entity(const u8 *SpriteData);
};

#endif

