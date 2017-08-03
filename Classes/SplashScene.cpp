#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

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

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Mr_Jump_Background.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Mr_Jump_Music_Level_1.wav");


	if (! CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Mr_Jump_Background.wav", true);
	}

	auto userdefault = UserDefault::getInstance();
	userdefault->setIntegerForKey("SOUNDLEVELID", -1);



	this->scheduleOnce(schedule_selector(SplashScene::gotoMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);

    return true;
}


void SplashScene::gotoMainMenuScene(float dt) {
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}