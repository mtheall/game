#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "struct.h"
#include "entity.h"

class Player: public Entity {
	private:
		vector2_t Input; //counters for tracking, Input is for accepting user input	
		int InputDirection;//Right, Down, Left, Up; make this 1,2,3, or 4 depending on which direction player is moving
	public:
		int AnimLoop;
		
		void AcceptUserInput(int BGid);
		void AUIReset();
		bool CheckPlayerCollision();
		
		friend class Map;
		friend class NPC;
		Player(const u8 *);
};

#endif

