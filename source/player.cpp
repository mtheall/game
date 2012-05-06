#include <nds.h>
#include <stdio.h>
#include "player.h"
#include "ghostly.h"

Player::Player(const u8 *ghostlyTiles) : Entity(ghostlyTiles) {
	Input.x=0; Input.y=0; 
	InputDirection=0; 
	AnimLoop=0; 
}

bool Player::CheckPlayerCollision() {
	return(true);
}

void Player::AcceptUserInput(int BGid) {

	int gfxOffset=0;
	
	///start of animation (loop=0)==========
	if(AnimLoop == 0) {
		scanKeys();
		if		(keysHeld() & KEY_RIGHT)	{Input.x =   1;	InputDirection=1;}
		else if	(keysHeld() & KEY_DOWN)		{Input.y =   1;	InputDirection=2;}
		else if	(keysHeld() & KEY_LEFT)		{Input.x =  -1;	InputDirection=3;}		
		else if	(keysHeld() & KEY_UP)		{Input.y =  -1;	InputDirection=4;}
		
		gfxOffset = ((InputDirection*2)-1) * 256*2;
		memcpy(pSpriteBase, ghostlyTiles+gfxOffset, 256*2);
	}
	
	///mid animation (loop=8)===============	
	if(AnimLoop == 8){
		gfxOffset = ((InputDirection-1)*2) * 256*2;
		//
		memcpy(pSpriteBase, ghostlyTiles+gfxOffset, 256*2);
	}
	
	AnimLoop+=1;

	if(CheckPlayerCollision() == true) {
		c_BGPixels.x += Input.x;
		c_BGPixels.y += Input.y;
	}
	else {
		AnimLoop+=1;
	}

	bgScroll(BGid, Input.x, Input.y);
	
	

}

void Player::AUIReset() {	
	AnimLoop=0;
	c_BGTiles.x += Input.x*2;
	c_BGTiles.y += Input.y*2;
	Input.x=0; 
	Input.y=0;
	InputDirection=0;
}

