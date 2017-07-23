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
	/* 
	Player* playerNode = (Player *)CSLoader::createNode("Player.csb");
	
	cocostudio::timeline::ActionTimeline *actionTimeline = CSLoader::createTimeline("Player.csb");
	playerNode->runAction(actionTimeline);
	actionTimeline->gotoFrameAndPlay(0, true);
	*/
	

	auto player = (MrJump *)Sprite::create("Jump.png");

	return player;
}

cocos2d::Point MrJump::getPositionTiled(cocos2d::TMXTiledMap *tileMap) {
	Point playerPosition;
	TMXObjectGroup *playerObjects = tileMap->getObjectGroup("playerObjects");
	auto playerOb = playerObjects->getObject("player");
	if (!playerOb.empty()) {		
		playerPosition.x = playerOb["x"].asInt();
		playerPosition.y = playerOb["y"].asInt();
	}
	return playerPosition;
}


cocos2d::RepeatForever* MrJump::runing() {
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
	cocos2d::RepeatForever *repeat = cocos2d::RepeatForever::create(animate);

	return repeat;
}