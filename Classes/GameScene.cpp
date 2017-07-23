#include "GameScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics(); 
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	// scene->getPhysicsWorld()->setGravity(cocos2d::Vec2(0, -9));

    
    // 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

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
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

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

	/* init box for world */ 
	auto edgeBody = PhysicsBody::createEdgeBox(cocos2d::Size( visibleSize.width, 50), PHYSICSSHAPE_MATERIAL_DEFAULT, 3.0F);
	edgeBody->setDynamic(false);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x,  origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);




	/* init player object */
	mrJump = MrJump::create();
	// get position in the map 
	Point playerPosition = mrJump->getPositionTiled(level->getMapLevel());
	mrJump->setPosition(playerPosition.x, playerPosition.y);

	mrJump->getPhysicsBody()->setDynamic(true);
	this->addChild(mrJump, TAG_ZORDER::PLAYER);

	// run action 
//	mrJump->runAction(mrJump->runing());
	



	
	this->scheduleUpdate();

    return true;
}


void GameScene::update(float delta) {
	mrJump->setPositionX(mrJump->getPositionX() + 3);
}