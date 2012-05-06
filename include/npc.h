#pragma once
#ifndef NPC_H
#define NPC_H

#include "struct.h"
#include "player.h"

class NPC: public Entity {
	 private:
	 public:
		static int NPCCount;
		static NPC *NPCs[];
		int OamIndex;
		
		void Hold(Player *Player);
		
		NPC(const u8 *);
		~NPC();
};

#endif

