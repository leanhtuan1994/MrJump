#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player : public cocos2d::Node
{
public:

	Player();		
	virtual ~Player();

	static Player* create();

	cocos2d::Point getPositionTiled( cocos2d::TMXTiledMap *tileMap);

	

};

#endif // __PLAYER_H__
