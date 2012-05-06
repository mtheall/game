#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "struct.h"
#include "entity.h"

class Player: public Entity {
private:
  vector2_t Input; //counters for tracking, Input is for accepting user input
  direction_t InputDirection;//Right, Down, Left, Up; make this 1,2,3, or 4 depending on which direction player is moving
  int AnimLoop;

public:
  Player(const u8 *);

  void AcceptUserInput(int BGid);
  void AUIReset();
  bool CheckPlayerCollision();

  const vector2_t   getInput()     const { return Input;          }
  const direction_t getDirection() const { return InputDirection; }
  const int         getAnim()      const { return AnimLoop;       }
};

#endif

