#include "LevelSelectionScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"


#define FILEPATH_ROOTNODE_LEVELSELECTIONSCENE		"LevelSelectionScene.csb"
#define CHILD_NAME_BUTTON_CLOSESCENE				"btnCloseScene"
#define CHILD_NAME_BUTTON_PAGEVIEW					"PageView_LevelSelection"
#define CHILD_NAME_BUTTON_PANEL_LEVEL1				"Panel_Level_1"
#define CHILD_NAME_LABEL_HIGHEST_SCORE				"lblHighestScore"



USING_NS_CC;

using namespace cocostudio::timeline;

Scene* LevelSelectionScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = LevelSelectionScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LevelSelectionScene::init()
{
    
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ){
        return false;
    }
   
	/************************************************************************/
	/*	               ROOT NODE DESIGNED FROM COCOS STUDIO
	/************************************************************************/
	auto rootNode = CSLoader::createNode(FILEPATH_ROOTNODE_LEVELSELECTIONSCENE);
    this->addChild(rootNode);



	/************************************************************************/
	/*						GET PAGE VIEW
	/************************************************************************/
	pageView = (cocos2d::ui::PageView *)rootNode->getChildByName(CHILD_NAME_BUTTON_PAGEVIEW);
	panelLevel1 = (cocos2d::ui::Layout *) pageView->getChildByName(CHILD_NAME_BUTTON_PANEL_LEVEL1);
	panelLevel1->addTouchEventListener([](cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			auto userdefault = UserDefault::getInstance();
			userdefault->setIntegerForKey("Level", 1);
			Director::getInstance()->replaceScene(TransitionMoveInB::create(TRANSITION_TIME, GameScene::createScene()));
			break;
		}
	});


	/************************************************************************/
	/*					 lblHighestScore
	/************************************************************************/
	this->lblHighestScore = (cocos2d::ui::Text *) panelLevel1->getChildByName(CHILD_NAME_LABEL_HIGHEST_SCORE);
	int currScore = (int) cocos2d::UserDefault::getInstance()->getFloatForKey(USER_DATA_KEY_HIGHT_SCORE);
	std::ostringstream scoreStream;
	scoreStream << currScore;
	std::string scoreString = scoreStream.str() + "%";
	this->lblHighestScore->setString(scoreString);




	/* INIT BUTTON TO CLOSE CURRENT SCENE TO REPLACE MAIN MENU SCENE */
	btnCloseScene = (cocos2d::ui::Button *) rootNode->getChildByName(CHILD_NAME_BUTTON_CLOSESCENE);
	btnCloseScene->addTouchEventListener([](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type ){
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			if (cocos2d::UserDefault::getInstance()->getIntegerForKey(USER_DATA_KEY_IS_PLAY_AUDIO_EFFECT) == USER_SETUP_AUDIO::TURN_ON) {
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FILEPATH_BUTTON_MUSIC_EFFECT);
			}
			break;
			/* Go to MainMenuScene if touch ended */
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(TransitionMoveInL::create(TRANSITION_TIME, MainMenuScene::createScene()));

			break;

		}
	});
	

    return true;
}

