
#include <nds.h>
#include <stdio.h>
#include "map.h"

Map::Map(int Layer, int MapBase, int TileBase, const u16 *Pal, const u8 *Tiles, const u16 *Map, int TileSize) {
  id = bgInit(Layer,
              BgType_Text8bpp,
              BgSize_T_512x256,
              MapBase,
              TileBase);
  bgSetPriority(id, Layer);

  // initialize bg palette
  memcpy(BG_PALETTE, Pal, 256*sizeof(u16));

  // copy tiles to VRAM
  memcpy(bgGetGfxPtr(id), Tiles, TileSize);

  // TODO: Rewrite to use c_bgTiles to load in for different starting positions
  // Map init
  for(int i = 0; i < 36; i++) {
    for(int j = 0; j < 36; j++)
      Buffer1[(i*32)+j] = Map[(i*256)+j];
  }
  for(int i = 0; i < 32; i++) {
    for(int j = 0; j < 32; j++)
      Buffer2[(i*32)+j] = Map[(i*256)+j+32];
  }
}

void Map::Update(Player *Player, const u16 MapData[]) {
  if(Player->getDirection() == DIR_RIGHT) {

    if((Player->getBGTiles().x % 64) < 32) {
      for(int j = 0; j < 2; j++) {
        for(int i = 0; i < 32; i++) {
          Buffer2[(((Player->getBGTiles().y+i)%32) *32)  + ((Player->getBGTiles().x+32+j)%32)] =
          MapData[ ((Player->getBGTiles().y+i)     *256) +  (Player->getBGTiles().x+32+j)];
        }
      }
    }
    else {
      for(int j = 0; j < 2; j++) {
        for(int i = 0; i < 32; i++) {
          Buffer1[(((Player->getBGTiles().y+i)%32) *32)  + ((Player->getBGTiles().x+32+j)%32)] =
          MapData[ ((Player->getBGTiles().y+i)     *256) +  (Player->getBGTiles().x+32+j)];
        }
      }
    }
  }
  else if(Player->getDirection() == DIR_DOWN) {
    int split = Player->getBGTiles().x % 32;

    if((Player->getBGTiles().x % 64) < 32) {
      for(int j = 0; j < 2; j++) {
        for(int i = 0; i < 32 - split; i++) {
          Buffer1[((((Player->getBGTiles().y+24)+j)%32) *32)  + (split+i)] =
          MapData[ (((Player->getBGTiles().y+24)+j)     *256) + (Player->getBGTiles().x+i)];
        }
        for(int i = 0; i < split; i++) {
          Buffer2[((((Player->getBGTiles().y+24)+j)%32) *32)  + (i)] =
          MapData[ (((Player->getBGTiles().y+24)+j)     *256) + (Player->getBGTiles().x+i+(32-split))];
        }
      }
    }
    else {
      for(int j = 0; j < 2; j++) {
        for(int i = 0; i < 32 - split; i++) {
          Buffer2[((((Player->getBGTiles().y+24)+j)%32) *32)  + (split+i)] =
          MapData[ (((Player->getBGTiles().y+24)+j)     *256) + (Player->getBGTiles().x+i)];
        }
        for(int i = 0; i < split; i++) {
          Buffer1[((((Player->getBGTiles().y+24)+j)%32) *32)  + (i)] =
          MapData[ (((Player->getBGTiles().y+24)+j)     *256) + (Player->getBGTiles().x+i+(32-split))];
        }
      }
    }
  }
  else if(Player->getDirection() == DIR_LEFT) {
    if((Player->getBGTiles().x % 64) < 33 && (Player->getBGTiles().x % 64) > 0) {
      for(int j = 0; j < 2; j++) {
        for(int i = 0; i < 32; i++) {
          Buffer1[(((Player->getBGTiles().y+i)%32) *32)  + ((Player->getBGTiles().x-(j+1))%32)] =
          MapData[ ((Player->getBGTiles().y+i)     *256) + (Player->getBGTiles().x-(j+1))];
        }
      }
    }
    else {
      for(int j = 0; j < 2; j++) {
        for(int i = 0; i < 32; i++) {
          Buffer2[(((Player->getBGTiles().y+i)%32) *32)  + ((Player->getBGTiles().x-(j+1))%32)] =
          MapData[ ((Player->getBGTiles().y+i)     *256) + (Player->getBGTiles().x-(j+1))];
        }
      }
    }
  }
  else if(Player->getDirection() == DIR_RIGHT) {
    int split = Player->getBGTiles().x % 32;

    if((Player->getBGTiles().x % 64) < 32)
      for(int j = 0; j < 2; j++) {
        for(int i = 0; i < 32 - split; i++) {
          Buffer1[((((Player->getBGTiles().y+32)-(j+1))%32) *32)  + (split+i)] =
          MapData[  ((Player->getBGTiles().y-    (j+1))     *256) + (Player->getBGTiles().x+i)];
        }
        for(int i = 0; i < split; i++) {
          Buffer2[((((Player->getBGTiles().y+32)-(j+1))%32)  *32) + (i)] =
          MapData[  ((Player->getBGTiles().y-    (j+1))     *256) + (Player->getBGTiles().x+i+(32-split))];
        }
      }
    else {
      for(int j = 0; j < 2; j++) {
        for(int i = 0; i < 32 - split; i++) {
          Buffer2[((((Player->getBGTiles().y+32)-  (j+1))%32)  *32)  + (split+i)] =
          MapData[  ((Player->getBGTiles().y-    (j+1))    *256) + (Player->getBGTiles().x+i)];
        }
        for(int i = 0; i < split; i++) {
          Buffer1[((((Player->getBGTiles().y+32)-(j+1))%32) *32)  + (i)] =
          MapData[  ((Player->getBGTiles().y-    (j+1))     *256) + (Player->getBGTiles().x+i+(32-split))];
        }
      }
    }
  }
}

void Map::BufferToMem() {
  // flush data cache
  DC_FlushRange(Buffer1, sizeof(Buffer1));
  DC_FlushRange(Buffer2, sizeof(Buffer2));

  // copy to VRAM
  dmaCopy(Buffer1, bgGetMapPtr(id),      2048);
  dmaCopy(Buffer2, bgGetMapPtr(id)+1024, 2048);
}

