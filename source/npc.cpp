#include <nds.h>
#include <stdio.h>
#include "npc.h"
#include "ghostly.h"

int NPC::NPCCount=0;
NPC *NPC::NPCs[32];

NPC::NPC(const u8 *SpriteData) : Entity(ghostlyTiles) {
	OamIndex = NPCCount;
	NPCCount++;
	NPCs[NPCCount] = this;
}

NPC::~NPC() {
	NPCCount--;
}

void NPC::Hold(Player *Player) {
	c_BGPixels.x -= Player->Input.x;
	c_BGPixels.y -= Player->Input.y;
	oamSetEntity(OamIndex+1, c_BGPixels.x, c_BGPixels.y, false);
}
