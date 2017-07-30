#include "GameScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameOverScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics(); 
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	/* set gravity for physics world */
	scene->getPhysicsWorld()->setGravity(cocos2d::Vec2(0.0f, -500.0f));

    
    // 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init(){
      
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }

	/* Get size */
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	limitedCameraPositionX = (visibleSize.width + origin.x) / 4;
	spaceCameraPositionX = visibleSize.width / 2 + origin.x - limitedCameraPositionX;
	isTouchTimeForJump = false;

	/*  Get level selected */
	auto userdefault = UserDefault::getInstance();
	this->currentLevelSelected = userdefault->getIntegerForKey("Level");


	/* init level map	  */
	this->level = new Level();
	if (currentLevelSelected == LEVEL_NAME::LEVEL_1) {
		level->loadMap("level1.tmx");
	}
	level->retain();
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
	mrJump->retain();
	// get position in the map 
	Point playerPosition = mrJump->getPositionTiled(level->getMapLevel());
	mrJump->setPosition(playerPosition.x, playerPosition.y);

	mrJump->getPhysicsBody()->setDynamic(true);
	this->addChild(mrJump, TAG_ZORDER::PLAYER);
	mrJump->runAction(mrJump->runningForever());
  

	/* init camera */
	cameraTarget = cocos2d::Sprite::create();
	cameraTarget->setPosition( visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y);
	cameraTarget->retain();
	this->addChild(cameraTarget);

	/* set camera follow target */
	camera = cocos2d::Follow::create(cameraTarget, cocos2d::Rect::ZERO);
	camera->retain();
	this->runAction(camera);


	/* Init Ground 	*/
	ground = new Ground();
	ground->getGroundDataInLevel(level->getMapLevel());	 
	ground->addGroundInScene(this);
	

	/* init Sea	*/
	sea = new Sea();
	sea->getSeaDataInLevel(level->getMapLevel());
	sea->addSeaInScene(this);
	

	/* listener touch event */
	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);


	/* listener physics contact */
	auto contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


	this->scheduleUpdate();
    return true;
}


void GameScene::update(float delta) {
	mrJump->setActionOfState();

	// stop jumping if over time define 
	if (isTouchTimeForJump && (cocos2d::utils::getTimeInMilliseconds() - timeTouchBegan > TIME_TOUCH_JUMP)) {
		this->scheduleOnce(schedule_selector(GameScene::stopJump), MRJUMP_JUMPING_DUARATION);
		isTouchTimeForJump = false;
	}

	// Update position camera and edgeNode follow mrJump
	cameraTarget->setPositionX( mrJump->getPositionX() < limitedCameraPositionX ? 
		visibleSize.width / 2 + origin.x : mrJump->getPositionX() + spaceCameraPositionX);
	edgeNode->setPositionX( cameraTarget->getPositionX());
}


bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
	CCLOG("Touch Began!");

	isTouchTimeForJump = true;

	this->timeTouchBegan = utils::getTimeInMilliseconds();
	CCLOG("Time touchbegan: %d", this->timeTouchBegan);

	mrJump->jump();

	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event) {
	CCLOG(" Touch Moved ");

}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
	CCLOG("Touch Ended !");

	/* stop jumping */
	if (isTouchTimeForJump) {
		this->scheduleOnce(schedule_selector(GameScene::stopJump), MRJUMP_JUMPING_DUARATION);
		isTouchTimeForJump = false;
		timeTouchBegan = 0;
	}
}


void GameScene::stopJump( float dt) {
	mrJump->stopJump();
}


bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact) {
	CCLOG(" onContactBegin");
	/* get physics contact */
	PhysicsBody *bodyA = contact.getShapeA()->getBody();
	PhysicsBody *bodyB = contact.getShapeB()->getBody();

	// Check if mr jump have collision with ground 
	if ((bodyA->getCollisionBitmask() == MRJUMP_COLLISION_BITMASK && bodyB->getCollisionBitmask() == GROUND_COLLISION_BITMASK) ||
		(bodyA->getCollisionBitmask() == GROUND_COLLISION_BITMASK && bodyB->getCollisionBitmask() == MRJUMP_COLLISION_BITMASK)) {

		mrJump->isGrounded = true;
		CCLOG(" MRJUMP + GROUND -> COLLISION ");
	}


	// Check if mr jump have collision with ground 
	if ((bodyA->getCollisionBitmask() == MRJUMP_COLLISION_BITMASK && bodyB->getCollisionBitmask() == ENEMY_COLLISION_BITMASK) ||
		(bodyA->getCollisionBitmask() == ENEMY_COLLISION_BITMASK && bodyB->getCollisionBitmask() == MRJUMP_COLLISION_BITMASK)) {

		CCLOG(" MRJUMP + ENEMY -> COLLISION -- DIE");
		gotoGameOverScene();
	}


	return true;
}


void GameScene::gotoGameOverScene(float dt) {
	auto gameOverScene = GameOverScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME_GAME_OVER, gameOverScene));
}









