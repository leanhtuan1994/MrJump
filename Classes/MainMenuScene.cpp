#include "MainMenuScene.h"
#include "LevelSelectionScene.h"
#include "Definitions.h"
#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#include "SplashScene.h"
#include "cocostudio/CocoStudio.h"


#define FILEPATH_ROOTNODE_MAINMENUSCENE		"MainMenuScene.csb"
#define CHILD_NAME_BUTTON_SETTING			"btnSetting"
#define CHILD_NAME_SPRITE_TAPTOPLAY			"spriteTapTopPlay"


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
	// SET MUSIC EFFECT FOR MAIN MENU SCENE
	setMusicEffect();


	/************************************************************************/
	/*			GET ROOT NODE DESIGN FROM COCOS STUDIO                                                                      
	/************************************************************************/
	auto rootNode = CSLoader::createNode(FILEPATH_ROOTNODE_MAINMENUSCENE);

	/* GET ACTION FROM CSB FILE */
	cocostudio::timeline::ActionTimeline *actionTimeline = CSLoader::createTimeline(FILEPATH_ROOTNODE_MAINMENUSCENE);
	rootNode->runAction(actionTimeline);
	actionTimeline->gotoFrameAndPlay(0, true);

    addChild(rootNode);

	/************************************************************************/
	/*          GET TAPTOPLAY SPRITE TO SET OPACITY FOLLOW UPDATE TIME 
	/************************************************************************/
	tapTopPlay = (Sprite *)rootNode->getChildByName(CHILD_NAME_SPRITE_TAPTOPLAY);



	/************************************************************************/
	/*                 LISTENER TOUCH EVENT FOR BUTTON SETTING 
	/*					TOUCH ENDED => GO TO SETTING SCENE			
	/************************************************************************/
	btnSetting = (cocos2d::ui::Button *) rootNode->getChildByName(CHILD_NAME_BUTTON_SETTING);
	btnSetting->addTouchEventListener([](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			auto scene = SettingScene::createScene();
			Director::getInstance()->replaceScene(TransitionMoveInL::create(TRANSITION_TIME, scene));
			break;
		}
	});


	/************************************************************************/
	/*		 LISTENER TOUCH EVENT TO SET GO TO THE LEVEL SELECTION SCENE                                                                   
	/************************************************************************/
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainMenuScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	/* SET UPDATE EVERY FRAME */
	this->scheduleUpdate();



    return true;
}


/* EVERY FRAME CALL UPDATE */
void MainMenuScene::update(float delta) {

	// Update Opacity for taptopplay sprite 
	if (tapTopPlay->getOpacity() <= 0) tapOpacity = 1;
	else if (tapTopPlay->getOpacity() >= 255) tapOpacity = -1;
	tapTopPlay->setOpacity(tapTopPlay->getOpacity() + tapOpacity);
}


/* SETTING WHEN TOUCH BEGAN */
bool MainMenuScene::onTouchBegan(Touch *touch, Event *unused_event) {
	gotoLevelSelectionScene();
	return true;
}

/* GO TO THE LEVEL SELECTION SCENE WHEN TOUCH BEGAN */
void MainMenuScene::gotoLevelSelectionScene() {
	auto scene = LevelSelectionScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInR::create(TRANSITION_TIME_MOVE_IN_R, scene));
}


/* SET MUSIC EFFECT IN THIS SCENE */
void MainMenuScene::setMusicEffect() {
	auto userdefault = UserDefault::getInstance();
	int isPlayBackgroundMusic = userdefault->getIntegerForKey(USER_DATA_KEY_IS_PLAY_BACKGROUND_MUSIC);
	int isPlayAudioEffect = userdefault->getIntegerForKey(USER_DATA_KEY_IS_PLAY_AUDIO_EFFECT);


	/* SET PLAY BACKGROUND MUSIC */
	if (isPlayBackgroundMusic == USER_SETUP_AUDIO::TURN_ON) {
		if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(FILEPATH_BACKGROUND_MUSIC, true);
		}
	} else {
		if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
	}


	/* GET ID MUSIC EFFECT THE THE LEVEL SCENE AND STOP IT */
	if (isPlayAudioEffect == USER_SETUP_AUDIO::TURN_ON) {

		int  soundLevelID = userdefault->getIntegerForKey(USER_DATA_KEY_MUSIC_EFFECT);
		if (soundLevelID != MUSIC_EFFECT_LEVEL_TURN_OFF) {
			CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundLevelID);
			userdefault->setIntegerForKey(USER_DATA_KEY_MUSIC_EFFECT, MUSIC_EFFECT_LEVEL_TURN_OFF);
		}
	}
}