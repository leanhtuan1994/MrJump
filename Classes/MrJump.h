#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class MrJump : public cocos2d::Sprite
{
public:

	MrJump();		
	virtual ~MrJump();

	static MrJump* create();

	cocos2d::Point getPositionTiled( cocos2d::TMXTiledMap *tileMap);

	cocos2d::RepeatForever *runing();
};

#endif // __PLAYER_H__
