#include "GameScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	/* Get size */
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*  Get level selected */
	auto userdefault = UserDefault::getInstance();
	this->currentLevelSelected = userdefault->getIntegerForKey("Level");

	/* init level map */
	this->level = new Level();
	if (currentLevelSelected == LEVEL_NAME::LEVEL_1) {
		level->loadMap("level1.tmx");
		level->retain();
	}
	this->addChild(level->getMapLevel(), TAG_ZORDER::MAP);
	

	player = Player::create();
	this->addChild(player, TAG_ZORDER::PLAYER);
	
	/* set position of player */
	Point playerPosition = player->getPositionTiled(level->getMapLevel());
	player->setPosition(playerPosition.x, playerPosition.y);


	
	this->scheduleUpdate();

    return true;
}


void GameScene::update(float delta) {
//	playerNode->setPositionX(playerNode->getPositionX() + 3);
}