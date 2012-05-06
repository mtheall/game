#include <nds.h>
#include <stdio.h>
#include "Classes.h"
#include "ghostly.h"

int NPCClass::NPCCount=0;
NPCClass *NPCClass::NPCs[32];

NPCClass::NPCClass(const u8 *SpriteData) : EntityClass(ghostlyTiles) {
	OamIndex = NPCCount;
	NPCCount++;
	NPCs[NPCCount] = this;
}

NPCClass::~NPCClass() {
	NPCCount--;
}

void NPCClass::Hold(PlayerClass *Player) {
	c_BGPixels.X -= Player->Input.X;
	c_BGPixels.Y -= Player->Input.Y;
	oamSetEntity(OamIndex+1, c_BGPixels.X, c_BGPixels.Y, false);
}
