#include "MrJump.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

MrJump::MrJump() {

}

MrJump::~MrJump() {
	
}


MrJump * MrJump::create() {
	/* create sprite */
	auto player = (MrJump *)Sprite::createWithSpriteFrameName("Jump1.png");

	player->isGrounded = true;

	/* init physics body */
	auto body = cocos2d::PhysicsBody::createBox(cocos2d::Size(player->getContentSize().width - 5, player->getContentSize().height - 8), 
		cocos2d::PhysicsMaterial(1.0f, 0.0f, 1.0f));
	body->setRotationEnable(false);
	body->setLinearDamping(1.0f);
	body->setDynamic(true);

	/* set collision bitmask */
	body->setCollisionBitmask(MRJUMP_COLLISION_BITMASK);
	body->setContactTestBitmask(true);
														 
	/* set physics body for sprite */
	player->setPhysicsBody(body);

	player->state = STATE::RUN;
	return player;
}

cocos2d::Point MrJump::getPositionTiled(cocos2d::TMXTiledMap *tileMap) {
	Point playerPosition;
	
	/* get player object in level tiled map */
	TMXObjectGroup *playerObjects = tileMap->getObjectGroup("playerObjects");
	auto playerOb = playerObjects->getObject("player");

	if (!playerOb.empty()) {		
		playerPosition.x = playerOb["x"].asInt();
		playerPosition.y = playerOb["y"].asInt();
	}

	return playerPosition;
}


void MrJump::runningAction() {
	int numFrame = NUM_FRAME_ANIMATION_JUMP;

	cocos2d::Vector<cocos2d::SpriteFrame *> frames;
	cocos2d::SpriteFrameCache *frameCache = cocos2d::SpriteFrameCache::getInstance();

	char file[100] = { 0 };

	for (int i = 0; i < numFrame; i++) {
		sprintf(file, "Jump%d.png", i + 1);
		cocos2d::SpriteFrame *frame = frameCache->getSpriteFrameByName(file);
		frames.pushBack(frame);
	}

	cocos2d::Animation *animation = cocos2d::Animation::createWithSpriteFrames(frames, ANIMATION_DELAY_TIME_JUMP);
	cocos2d::Animate *animate = cocos2d::Animate::create(animation);

	this->runningForever = cocos2d::RepeatForever::create(animate);
	this->runningForever->retain();

	this->runAction(this->runningForever);
}


void MrJump::stopRunningAction() {
	this->stopAction(this->runningForever);
}


void MrJump::setActionOfState() {
	switch (state) {
	case RUN:
		this->setPositionX(this->getPositionX() + MRJUMP_RUNNING_SPEED);
		break;

	case JUMP:
		this->setPositionX(this->getPositionX() + MRJUMP_RUNNING_SPEED);
		this->setPositionY(this->getPositionY() + 9.2f);
		break;

	case DEAD:

		break;
	}
}