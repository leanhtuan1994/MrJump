#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"



#define FILEPATH_ROOTNODE_SPLASH_SCENE  "SplashScene.csb"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	/************************************************************************/
	/*			GET ROOT NODE DESIGN FROM COCOS STUDIO
	/************************************************************************/
	auto rootNode = CSLoader::createNode(FILEPATH_ROOTNODE_SPLASH_SCENE);
	this->addChild(rootNode);



	/************************************************************************/
	/*		PRELOAD AUDIO EFFECT IN THE PROJECT                                                                     
	/************************************************************************/
	auto userdefault = UserDefault::getInstance();
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(FILEPATH_BACKGROUND_MUSIC);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(FILEPATH_LEVEL_MUSIC_EFFECT);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(FILEPATH_BUTTON_MUSIC_EFFECT);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(FILEPATH_DEATH_MUSIC_EFFECT);

//	UserDefault::getInstance()->setFloatForKey(USER_DATA_KEY_HIGHT_SCORE, 0);



	/*	CHECK AND PLAY BACKGROUND MUSIC */	
	int isPlayBackgroundMusic = userdefault->getIntegerForKey(USER_DATA_KEY_IS_PLAY_BACKGROUND_MUSIC);

	if (isPlayBackgroundMusic == USER_SETUP_AUDIO::TURN_ON) {
		if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(FILEPATH_BACKGROUND_MUSIC, true);
		}
	} else  {
		if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
	}



	/*	SET NOT PLAY EFFECT FOR THE GAME LEVEL 	*/
	userdefault->setIntegerForKey(USER_DATA_KEY_MUSIC_EFFECT, MUSIC_EFFECT_LEVEL_TURN_OFF);


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("JumpAni.plist", "JumpAni.png");



	/************************************************************************/
	/*			SET UPDATE ONE TIME TO REPLACE SCENE - MAIN MENU SCENE                                                                     
	/************************************************************************/
	this->scheduleOnce(schedule_selector(SplashScene::gotoMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);



    return true;
}


void SplashScene::gotoMainMenuScene(float dt) {
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}