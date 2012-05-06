
#include <nds.h>
#include <stdio.h>
#include "Classes.h"
#include "ghostly.h"

PlayerClass::PlayerClass(const u8 *ghostlyTiles) : EntityClass(ghostlyTiles) {
	Input.X=0; Input.Y=0; 
	InputDirection=0; 
	AnimLoop=0; 
}

bool PlayerClass::CheckPlayerCollision() {
	return(true);
}

void PlayerClass::AcceptUserInput(int BGid) {

	int gfxOffset=0;
	
	///start of animation (loop=0)==========
	if(AnimLoop == 0) {
		scanKeys();
		if		(keysHeld() & KEY_RIGHT)	{Input.X =   1;	InputDirection=1;}
		else if	(keysHeld() & KEY_DOWN)		{Input.Y =   1;	InputDirection=2;}
		else if	(keysHeld() & KEY_LEFT)		{Input.X =  -1;	InputDirection=3;}		
		else if	(keysHeld() & KEY_UP)		{Input.Y =  -1;	InputDirection=4;}
		
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
		c_BGPixels.X += Input.X;
		c_BGPixels.Y += Input.Y;
	}
	else {
		AnimLoop+=1;
	}

	bgScroll(BGid, Input.X, Input.Y);
	
	

}

void PlayerClass::AUIReset() {	
	AnimLoop=0;
	c_BGTiles.X += Input.X*2;
	c_BGTiles.Y += Input.Y*2;
	Input.X=0; 
	Input.Y=0;
	InputDirection=0;
}

