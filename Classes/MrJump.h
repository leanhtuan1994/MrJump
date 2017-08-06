#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"


enum STATE {
	RUN,
	JUMP,
	DEAD
};


class MrJump : public cocos2d::Sprite
{
public:

	MrJump();		
	virtual ~MrJump();

	static MrJump* create();

	cocos2d::Point getPositionTiled( cocos2d::TMXTiledMap *tileMap);

	cocos2d::RepeatForever *runningForever;

	void runningAction();
	void stopRunningAction();


	void jump() {
		state = STATE::JUMP;
	}

	void stopJump() {
		state = STATE::RUN;
	}

	void die() {
		state = STATE::DEAD;

		/* action for die */
		auto actionMoveBy = cocos2d::MoveBy::create(0.35f, cocos2d::Point(-120.0f, 200.0f));
		auto actionRotate = cocos2d::RotateBy::create(0.2f, -90.0f);
		this->runAction(actionMoveBy);
		this->runAction(actionRotate);
	}

	bool isGrounded;

	void setActionOfState();

	/* attributes of mr jump */
	STATE state;

	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

};

#endif // __PLAYER_H__
