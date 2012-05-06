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

#include "struct.h"
#include "map.h"
#include "npc.h"

#include "layer1.h"
#include "ghostly.h"

void TestZone() {
  int loop;

  Map    *map     = new Map(3, 0, 1, layer1Pal, layer1Tiles, layer1Map, layer1TilesLen);
  Player *player  = new Player(ghostlyTiles);
  NPC    *NPCTest = new NPC(ghostlyTiles);

  player->oamSetEntity(0, 15*8, 10*8, false);
  NPCTest->oamSetEntity(1, 0, 0, false);

  while(1) {
    // wait for VBlank
    swiWaitForVBlank();
    // update VRAM
    map->BufferToMem();
    // update background registers
    bgUpdate();
    // update OAM
    oamUpdate(&oamMain);
    // gather input
    scanKeys();

    if((keysHeld() & (KEY_RIGHT|KEY_DOWN|KEY_LEFT|KEY_UP)) || player->getAnim() != 0)
      player->AcceptUserInput(map->getID());

    if(player->getAnim() == 1)
      map->Update(player, layer1Map);

    for(loop=0;loop<NPC::NPCCount;loop++)
      NPC::NPCs[loop]->Hold(player);

    if(player->getAnim() == 16)
      player->AUIReset();
  }
}

int main(int argc, char *argv[]) {
  // initialize video
  videoSetMode(MODE_0_2D);
  vramSetPrimaryBanks(VRAM_A_MAIN_BG,
                      VRAM_B_MAIN_SPRITE,
                      VRAM_C_SUB_BG,
                      VRAM_D_SUB_SPRITE);

  // initialize console demo
  consoleDemoInit();

  // initialize OAM
  oamInit(&oamMain, SpriteMapping_1D_128, false);
  // initialize the sprite palette
  memcpy(SPRITE_PALETTE, ghostlyPal, ghostlyPalLen);

  // run the Test Zone
  TestZone();

  return 0;
}

