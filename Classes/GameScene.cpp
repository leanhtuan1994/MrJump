#include "GameScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "SplashScene.h"


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics(); 
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	/* set gravity for physics world */
	scene->getPhysicsWorld()->setGravity(cocos2d::Vec2(GAME_GRAVITY));

    
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

	/* Get visibleSize and origin from device	*/
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	/*	SET limitedCameraPositionX to don't move camera when camera target position x < 1/4 width */
	limitedCameraPositionX = (visibleSize.width + origin.x) / 4;

	/* 
	*	SET space width Camera - Mr Jump 
	*	Camera =  1/2 width  
	*	Mr Jump  =  1/4 
	*/
	spaceCameraPositionX = visibleSize.width / 2 + origin.x - limitedCameraPositionX;

	/* 	SET limited time for touch to jump mr.jump */
	isTouchTimeForJump = false;

	/* INIT number of jumped */
	this->numberJumped = 0;
	percentWidthOfMrJump = 0;

	/*  Get level selected */
	userDafault = UserDefault::getInstance();
	this->currentLevelSelected = userDafault->getIntegerForKey("Level");


	/* init data is 0 */
	this->userDafault->setIntegerForKey(USER_DATA_KEY_NUMBER_JUMPS, 0);
	this->userDafault->setIntegerForKey(USER_DATA_KEY_SCORE_PERCENT, 0);


	/************************************************************************/
	/*							PLAY MUSIC
	/************************************************************************/
	int isPlayBackgroundMusic = userDafault->getIntegerForKey(USER_DATA_KEY_IS_PLAY_BACKGROUND_MUSIC);
	int isPlayAudioEffect = userDafault->getIntegerForKey(USER_DATA_KEY_IS_PLAY_AUDIO_EFFECT);

	if ( (isPlayBackgroundMusic == USER_SETUP_AUDIO::TURN_ON )
		&& (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) ) {
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}


	this->soundLevelID = userDafault->getIntegerForKey(USER_DATA_KEY_MUSIC_EFFECT);
	if (isPlayAudioEffect == USER_SETUP_AUDIO::TURN_ON) {
		if (this->soundLevelID == MUSIC_EFFECT_LEVEL_TURN_OFF) {
			if (this->currentLevelSelected == LEVEL_NAME::LEVEL_1) {
				this->soundLevelID = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FILEPATH_LEVEL_MUSIC_EFFECT, true);
				userDafault->setIntegerForKey(USER_DATA_KEY_MUSIC_EFFECT, this->soundLevelID);
			}
		}
	}



	/* init level map */
	this->level = new Level();

	/* SET LEVEL IN THE GAME */
	if (currentLevelSelected == LEVEL_NAME::LEVEL_1) {
		level->loadMap("level1.tmx");
	}
	/* RETAIN Level to the scene */
	level->retain();
	/* ADD LEVEL IN THE SCENE */
	this->addChild(level->getMapLevel(), TAG_ZORDER::MAP);
	

	/************************************************************************/
	/*                SET BOX IN THE SCENE									*/
	/************************************************************************/

	auto edgeBody = PhysicsBody::createEdgeBox(
		cocos2d::Size( visibleSize.width+ origin.x, visibleSize.height + origin.y), 
		PHYSICSSHAPE_MATERIAL_DEFAULT, 5.0F);
	edgeBody->setDynamic(false);
	edgeNode = Node::create();
	edgeNode->setPosition( visibleSize.width /2 + origin.x , visibleSize.height/2 + origin.y);
	edgeNode->setPhysicsBody(edgeBody);
//	this->addChild(edgeNode);



	/************************************************************************/
	/*								INIT MR JUMP							*/				
	/************************************************************************/
	mrJump = MrJump::create();	
	mrJump->retain();
	mrJump->setPosition(mrJump->getPositionTiled(level->getMapLevel()));
	this->addChild(mrJump, TAG_ZORDER::PLAYER);
	mrJump->runningAction();
  

	/************************************************************************/
	/*						INIT CAMERA TO FOLLOW MR JUMP 
	/************************************************************************/
	cameraTarget = cocos2d::Sprite::create();
	cameraTarget->setPosition( visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y);
	cameraTarget->retain();
	this->addChild(cameraTarget);
	/* set camera follow target */
	camera = cocos2d::Follow::create(cameraTarget, cocos2d::Rect::ZERO);
	camera->retain();
	this->runAction(camera);


	/************************************************************************/
	/*						INIT GROUND OBJECTS                                                                   
	/************************************************************************/
	ground = new Ground();
	ground->getGroundDataInLevel(level->getMapLevel());	 
	ground->addGroundInScene(this);
	

	/************************************************************************/
	/*							INIT SEA OBJECTS                                                                     
	/************************************************************************/
	sea = new Sea();
	sea->getSeaDataInLevel(level->getMapLevel());
	sea->addSeaInScene(this);
	

	/************************************************************************/
	/*							INIT HAZARD
	/************************************************************************/

	hazard = new Hazard();
	hazard->getHazardDataInLevel(level->getMapLevel());
	hazard->addHazardInScene(this);




	/************************************************************************/
	/*					LISTENER TOUCH EVENT                                                                      
	/************************************************************************/
	touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);



	/************************************************************************/
	/*					LISTENER CONTACT COLLISION 
	/************************************************************************/
	contactListener = cocos2d::EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(GameScene::onContactSeparate, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	

	/* UPDATE EVERY FRAME */
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
//	edgeNode->setPositionX( cameraTarget->getPositionX());

}


bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
	CCLOG("Touch Began!");

	isTouchTimeForJump = true;

	this->timeTouchBegan = utils::getTimeInMilliseconds();

	if (mrJump->isGrounded) {
		this->numberJumped++;
		mrJump->jump();

		CCLOG("NUMBER JUMPED : %d", this->numberJumped);
	}

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
	if ((bodyA->getCollisionBitmask() == MRJUMP_COLLISION_BITMASK && bodyB->getCollisionBitmask() == HAZARD_COLLISION_BITMASK) ||
		(bodyA->getCollisionBitmask() == HAZARD_COLLISION_BITMASK && bodyB->getCollisionBitmask() == MRJUMP_COLLISION_BITMASK)) {

		CCLOG(" MRJUMP + ENEMY -> COLLISION -- DIE");
		this->setStatusMrJumpDie();
	}

	return true;
}


void GameScene::onContactSeparate(cocos2d::PhysicsContact &contact) {
	/* get physics contact */
	PhysicsBody *bodyA = contact.getShapeA()->getBody();
	PhysicsBody *bodyB = contact.getShapeB()->getBody();

	// Check if mr jump have collision with ground 
	if ((bodyA->getCollisionBitmask() == MRJUMP_COLLISION_BITMASK && bodyB->getCollisionBitmask() == GROUND_COLLISION_BITMASK) ||
		(bodyA->getCollisionBitmask() == GROUND_COLLISION_BITMASK && bodyB->getCollisionBitmask() == MRJUMP_COLLISION_BITMASK)) {

		mrJump->isGrounded = false;
		CCLOG("onContactSeparate");
	}
}



void GameScene::addGameOverLayer() {
	auto gameOverLayer = GameOverScene::create();

	gameOverLayer->setPosition( cameraTarget->getPositionX() - visibleSize.width/2 - origin.x, 
		cameraTarget->getPositionY() - visibleSize.height/2 - origin.y);

	this->addChild(gameOverLayer, GAMEOVERLAYER);
}


void GameScene::setStatusMrJumpDie() {
	this->mrJump->die();

	mrJump->stopRunningAction();
	this->getEventDispatcher()->removeEventListener(touchListener);
	this->getEventDispatcher()->removeEventListener(contactListener);

	/* counting percent width of mr jump */
	this->percentWidthOfMrJump = mrJump->getPositionX() / level->getWidth() * 100;
	CCLOG("PERCENT WIDTH: %d", this->percentWidthOfMrJump);

	/* turn of update */
	this->unscheduleUpdate();


	/* Save data */
	this->userDafault->setIntegerForKey(USER_DATA_KEY_NUMBER_JUMPS, this->numberJumped);
	this->userDafault->setIntegerForKey(USER_DATA_KEY_SCORE_PERCENT, this->percentWidthOfMrJump);


	this->addGameOverLayer();
}





