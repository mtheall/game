

#include <nds.h>

#include "Structs.h"

#ifndef CLASSES_H
#define CLASSES_H

class PlayerClass;

class MapClass{
		private:
			u16 Buffer1[32*32], Buffer2[32*32];
		public:
			int id;
			MapClass(int Layer, int MapBase, int TileBase, const u16 *Pal, const u8 *Tiles, const u16 *Map, int TileSize);
			
			void Init(const u16*, const u16*, const u16*, int);
			void Update(PlayerClass *, const u16[]);
			void BufferToMem();
};

class EntityClass{
	private:
	protected:
		u16 *pSpriteBase;
		XY c_BGPixels, c_BGTiles;
	public:
		void oamSetEntity(int Index, int X, int Y, bool Hide);	
		
		EntityClass(const u8 *SpriteData);
};

class PlayerClass: public EntityClass {
	private:
		XY Input; //counters for tracking, Input is for accepting user input	
		int InputDirection;//Right, Down, Left, Up; make this 1,2,3, or 4 depending on which direction player is moving
	public:
		int AnimLoop;
		
		void AcceptUserInput(int BGid);
		void AUIReset();
		bool CheckPlayerCollision();
		
		friend class MapClass;
		friend class NPCClass;
		PlayerClass(const u8 *);
};
	
class NPCClass: public EntityClass {
	 private:
	 public:
		static int NPCCount;
		static NPCClass *NPCs[];
		int OamIndex;
		
		void Hold(PlayerClass *Player);
		
		NPCClass(const u8 *);
		~NPCClass();
};

#endif
