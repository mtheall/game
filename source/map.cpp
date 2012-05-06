
#include <nds.h>
#include <stdio.h>
#include "map.h"

Map::Map(int Layer, int MapBase, int TileBase, const u16 *Pal, const u8 *Tiles, const u16 *Map, int TileSize) {

	int i=0, j=0;
	
	id = bgInit(Layer,
	 			BgType_Text8bpp,
	 			BgSize_T_512x256,
	 			MapBase,
	 			TileBase 
	 			);
	bgSetPriority(id, Layer);
	
	//Palette init
	memcpy(BG_PALETTE, Pal, 256);
	
	//Tile init
    memcpy(BG_TILE_RAM(1), Tiles, TileSize);
	
	///Rewrite to use c_bgTiles to load in for different starting positions
	//Map init
	for(i=0;i<36;i++){
		for(j=0;j<36;j++){
			Buffer1[(i*32)+j] = Map[(i*256)+j];
		}
	}
	for(i=0;i<32;i++){
		for(j=0;j<32;j++){
			Buffer2[(i*32)+j] = Map[(i*256)+j+32];
		}
	}
}

void Map::Update(Player *Player, const u16 MapData[]){

	int i=0, j=0, split=0;
	
	if(Player->InputDirection==1){
		
		if((Player->c_BGTiles.x % 64) < 32){
			for(j=0;j<2;j++){
				for(i=0;i<32;i++){	
					Buffer2	[(((Player->c_BGTiles.y+i)%32)	*32) 	+ ((Player->c_BGTiles.x+32+j)%32)] =
					MapData	[ ((Player->c_BGTiles.y+i)	  	*256)	+  (Player->c_BGTiles.x+32+j)];
				}
			}
		}
		else{
			for(j=0;j<2;j++){
				for(i=0;i<32;i++){
					Buffer1	[(((Player->c_BGTiles.y+i)%32)	*32) 	+ ((Player->c_BGTiles.x+32+j)%32)] =
					MapData	[ ((Player->c_BGTiles.y+i)	  	*256)	+  (Player->c_BGTiles.x+32+j)];
				}
			}
		}
	}
	else if(Player->InputDirection==2) {
		
		split = Player->c_BGTiles.x % 32;
		
		if((Player->c_BGTiles.x % 64) < 32)
			for(j=0;j<2;j++){
				for(i=0;i<32 - split;i++) {
					Buffer1	[((((Player->c_BGTiles.y+24)+j)%32)	*32)  + (split+i)] = 
					MapData	[ (((Player->c_BGTiles.y+24)+j)		*256) + (Player->c_BGTiles.x+i)];
				}
				for(i=0;i<split;i++) {
					Buffer2	[((((Player->c_BGTiles.y+24)+j)%32)	*32)  + (i)] = 
					MapData	[ (((Player->c_BGTiles.y+24)+j)		*256) + (Player->c_BGTiles.x+i+(32-split))];
				}
			}
		else {
			for(j=0;j<2;j++){
				for(i=0;i<32 - split;i++) {
					Buffer2	[((((Player->c_BGTiles.y+24)+j)%32)	*32)  + (split+i)] = 
					MapData	[ (((Player->c_BGTiles.y+24)+j)		*256) + (Player->c_BGTiles.x+i)];
				}
				for(i=0;i<split;i++) {
					Buffer1	[((((Player->c_BGTiles.y+24)+j)%32)	*32)  + (i)] = 
					MapData	[ (((Player->c_BGTiles.y+24)+j)		*256) + (Player->c_BGTiles.x+i+(32-split))];
				}
			}
		}
	}
	else if(Player->InputDirection==3) {
		if((Player->c_BGTiles.x % 64) < 33 && (Player->c_BGTiles.x % 64) > 0){
			for(j=0;j<2;j++){
				for(i=0;i<32;i++){
					Buffer1	[(((Player->c_BGTiles.y+i)%32)	*32) 	+ ((Player->c_BGTiles.x-(j+1))%32)] =
					MapData	[ ((Player->c_BGTiles.y+i)		*256)	+ (Player->c_BGTiles.x-(j+1))];
				}
			}
		}
		else {
			for(j=0;j<2;j++){
				for(i=0;i<32;i++){
					Buffer2	[(((Player->c_BGTiles.y+i)%32)	*32) 	+ ((Player->c_BGTiles.x-(j+1))%32)] =
					MapData	[ ((Player->c_BGTiles.y+i)		*256)	+ (Player->c_BGTiles.x-(j+1))];
				}
			}
		}
	}
	else if(Player->InputDirection==4) {
	
		split = Player->c_BGTiles.x % 32;
		
		if((Player->c_BGTiles.x % 64) < 32)
			for(j=0;j<2;j++){
				for(i=0;i<32 - split;i++) {
					Buffer1	[((((Player->c_BGTiles.y+32)-	(j+1))%32)	*32)  + (split+i)] = 
					MapData	[  ((Player->c_BGTiles.y-		(j+1))		*256) + (Player->c_BGTiles.x+i)];
				}
				for(i=0;i<split;i++) {
					Buffer2	[((((Player->c_BGTiles.y+32)-	(j+1))%32)	*32)  + (i)] = 
					MapData	[  ((Player->c_BGTiles.y-		(j+1))	  	*256) + (Player->c_BGTiles.x+i+(32-split))];
				}
			}
		else{
			for(j=0;j<2;j++){
				for(i=0;i<32 - split;i++) {
					Buffer2	[((((Player->c_BGTiles.y+32)-	(j+1))%32)	*32)  + (split+i)] = 
					MapData	[  ((Player->c_BGTiles.y-		(j+1))		*256) + (Player->c_BGTiles.x+i)];
				}
				for(i=0;i<split;i++) {
					Buffer1	[((((Player->c_BGTiles.y+32)-	(j+1))%32)	*32)  + (i)] = 
					MapData	[  ((Player->c_BGTiles.y-		(j+1))		*256) + (Player->c_BGTiles.x+i+(32-split))];
				}
			}
		}
	}
}

void Map::BufferToMem() {
	dmaCopy(Buffer1, BG_MAP_RAM(0), 2048);
	dmaCopy(Buffer2, BG_MAP_RAM(1), 2048);
}
