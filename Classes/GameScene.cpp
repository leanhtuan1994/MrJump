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

	/* set gravity for physics world */
	//scene->getPhysicsWorld()->setGravity(cocos2d::Vec2(0.0f, -10.0f));

    
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
	int bodyHeight = level->getMapLevel()->getMapSize().width * level->getMapLevel()->getTileSize().width;
	auto edgeBody = PhysicsBody::createEdgeBox(cocos2d::Size( visibleSize.width+ origin.x, visibleSize.height + origin.y), PHYSICSSHAPE_MATERIAL_DEFAULT, 1.0F);
	edgeBody->setDynamic(false);
	edgeNode = Node::create();
	edgeNode->setPosition( visibleSize.width /2 + origin.x , visibleSize.height/2 + origin.y);
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);

	/* init player object */
	mrJump = MrJump::create();
	// get position in the map 
	Point playerPosition = mrJump->getPositionTiled(level->getMapLevel());
	mrJump->setPosition(playerPosition.x, playerPosition.y);

	mrJump->getPhysicsBody()->setDynamic(true);
	this->addChild(mrJump, TAG_ZORDER::PLAYER);
	mrJump->runAction(mrJump->runing());

	/* init camera */
	cameraTarget = cocos2d::Sprite::create();
	cameraTarget->setPosition( visibleSize.width/2 + origin.x, visibleSize.height / 2 + origin.y);
	cameraTarget->retain();
	this->addChild(cameraTarget);

	camera = cocos2d::Follow::create(cameraTarget, cocos2d::Rect::ZERO);
	camera->retain();
	this->runAction(camera);



	/* Init Ground */
	ground = new Ground();
	ground->getGroundDataInLevel(level->getMapLevel());
	ground->addGroundInScene(this);

	this->scheduleUpdate();

    return true;
}


void GameScene::update(float delta) {
	/* move mr jump */
	mrJump->setPositionX(mrJump->getPositionX() + 5.5f);

	// Update position camera and edgeNode follow mrJump
	cameraTarget->setPositionX(visibleSize.width / 2  + origin.x > mrJump->getPositionX() ? visibleSize.width/2 + origin.x : mrJump->getPositionX());
	edgeNode->setPositionX( cameraTarget->getPositionX());
}