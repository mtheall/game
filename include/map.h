#pragma once
#ifndef MAP_H
#define MAP_H

#include <nds.h>
#include "player.h"

class Map{
		private:
			u16 Buffer1[32*32], Buffer2[32*32];
		public:
			int id;
			Map(int Layer, int MapBase, int TileBase, const u16 *Pal, const u8 *Tiles, const u16 *Map, int TileSize);
			
			void Init(const u16*, const u16*, const u16*, int);
			void Update(Player *, const u16[]);
			void BufferToMem();
};

#endif

