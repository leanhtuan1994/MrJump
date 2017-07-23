#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player : public cocos2d::Node
{
public:

	Player();		
	virtual ~Player();

	static Player* create();

	

};

#endif // __PLAYER_H__
