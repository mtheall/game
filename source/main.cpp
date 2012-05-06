
///
///either allocategfx is giving a bad pointer, or ?
///

/*ToDo
 *
 *draw npcs - done
 *npchold - done
 *npcmovement
 *animate npcs
 *move to pokemon style priority for entities
 *
 *next block: dynamic collision map and sprite movement restricted to area around Player->
 */

#include <nds.h>
#include <stdio.h>
#include <_ansi.h>

#include "struct.h"
#include "map.h"
#include "npc.h"

///Gfx includes
//Maps
#include "layer1.h"
//Sprites
#include "ghostly.h"

void TestZone() {
	int loop;
	
	///Objects==================================///
	Map 	*map = 		new Map(3, 0, 1, layer1Pal, layer1Tiles, layer1Map, layer1TilesLen);
	Player *player = 	new Player(ghostlyTiles);
	NPC 	*NPCTest =	new NPC(ghostlyTiles);
	///========================================///

	player->oamSetEntity(0, 15*8, 10*8, false);
	NPCTest->oamSetEntity(1, 0, 0, false);
	
	///MAIN LOOP==============================================================================
	while(1) {

	swiWaitForVBlank();
	map->BufferToMem();
	bgUpdate();
	oamUpdate(&oamMain);
	
	scanKeys();
	if(keysHeld() & (KEY_RIGHT|KEY_DOWN|KEY_LEFT|KEY_UP) || player->AnimLoop != 0) {
		player->AcceptUserInput(map->id); 	
	} 
	if(player->AnimLoop == 1){
		map->Update(player, layer1Map);
	}
	for(loop=0;loop<NPC::NPCCount;loop++) {NPC::NPCs[loop]->Hold(player);}///Holds NPCs in place
	
	if(player->AnimLoop == 16) {player->AUIReset();}
	
	}///======================================================================================
}

//------------------------------------------------------
int main() {
//------------------------------------------------------
	
	///Game Init==============
	consoleDemoInit(); //Initlializes subscreen for printing functionality
	irqInit();
	irqEnable(IRQ_VBLANK);
	videoSetMode(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankB(VRAM_B_MAIN_SPRITE);
	oamInit(&oamMain, SpriteMapping_1D_32, false);// last argument for extended palette
	memcpy(SPRITE_PALETTE, ghostlyPal, ghostlyPalLen); //initialize stantard sprite palette, used for everything.
	///=======================
	
	TestZone();

    return 0;
}


