
#include <nds.h>

#include "Classes.h"

EntityClass::EntityClass(const u8 *SpriteData) {
	c_BGPixels.X=0;	c_BGPixels.Y=0;
	c_BGTiles.X=0; 	c_BGTiles.Y=0;

	pSpriteBase = oamAllocateGfx(&oamMain, SpriteSize_16x32, SpriteColorFormat_256Color);
	memcpy(pSpriteBase, SpriteData, 256*2);
}

void EntityClass::oamSetEntity(int index, int X, int Y, bool Hide)
{
	oamSet(&oamMain,
			index, 
			X, Y,
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