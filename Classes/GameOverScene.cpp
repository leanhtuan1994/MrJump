#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"



#define ROOT_NODE_NAME_GAMEOVERSCENE	"GameOverLayer.csb"
#define CHILD_NAME_BUTTON_PLAYAGIAN		"btnPlayAgain"
#define CHILD_NAME_BUTTON_CLOSELAYER	"btnCloseLayer"
#define CHILD_NAME_LABEL_NUMBERJUMPS	"lblNumberJumps"
#define CHILD_NAME_LABEL_SCOREPERCENT	"lblScorePercent"


USING_NS_CC;


// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ){
        return false;
    }

	/* init user data default */
	this->userDefault = cocos2d::UserDefault::getInstance();


	/************************************************************************/
	/*             INIT ROOT NODE DEIGNED BY COCOS STUDIO 
	/************************************************************************/
	auto rootNode = CSLoader::createNode(ROOT_NODE_NAME_GAMEOVERSCENE);

	// Run animation
	cocostudio::timeline::ActionTimeline *actionTimeline = CSLoader::createTimeline(ROOT_NODE_NAME_GAMEOVERSCENE);
	rootNode->runAction(actionTimeline);
	actionTimeline->gotoFrameAndPlay(0, false);

	this->addChild(rootNode);



	/************************************************************************/
	/*                GET UI LABLE NUMBER JUMPED FROM ROOT NODE 
	/************************************************************************/
	this->lblNumberJumps = (cocos2d::ui::Text *) rootNode->getChildByName(CHILD_NAME_LABEL_NUMBERJUMPS);
	int numJumps = this->userDefault->getIntegerForKey(USER_DATA_KEY_NUMBER_JUMPS);
	std::string numberJumpsString = std::to_string(numJumps) + " JUMPS";
	this->lblNumberJumps->setString(numberJumpsString);

	
	/************************************************************************/
	/*                GET UI LABLE SCORE FROM ROOT NODE
	/************************************************************************/
	this->lblScorePercent = (cocos2d::ui::Text *) rootNode->getChildByName(CHILD_NAME_LABEL_SCOREPERCENT);
	float currScore = this->userDefault->getFloatForKey(USER_DATA_KEY_SCORE_PERCENT); 
	std::string scoreString = std::to_string(int(currScore)) + "%";
	this->lblScorePercent->setString(scoreString);


	/* GET HIGHEST SCORE PERCENT */
	this->highestScorePercent = userDefault->getIntegerForKey(USER_DATA_KEY_HIGHT_SCORE);
	if (currScore > highestScorePercent) {
		userDefault->setFloatForKey(USER_DATA_KEY_HIGHT_SCORE, currScore);
	}


	/************************************************************************/
	/*                GET UI BUTTON PLAY AGIAN FROM ROOT NODE
	/*						LISTENER TOUCH EVENT 
	/************************************************************************/
	btnPlayAgain = (cocos2d::ui::Button *) rootNode->getChildByName(CHILD_NAME_BUTTON_PLAYAGIAN);
	btnPlayAgain->addTouchEventListener([](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			auto gameScene = GameScene::createScene();
			cocos2d::Director::getInstance()->replaceScene(TransitionMoveInT::create(TRANSITION_TIME, gameScene));
			break;
		}
	});


	/************************************************************************/
	/*                GET UI BUTTON CLOSE LAYER FROM ROOT NODE
	/*						LISTENER TOUCH EVENT
	/*					REPLACE SCENE TO MAIN MENU SCENE 
	/************************************************************************/
	btnCloseLayer = (cocos2d::ui::Button *) rootNode->getChildByName(CHILD_NAME_BUTTON_CLOSELAYER);
	btnCloseLayer->addTouchEventListener([](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			/* pause music */
			auto menuScene = MainMenuScene::createScene();
			cocos2d::Director::getInstance()->replaceScene(TransitionMoveInL::create(TRANSITION_TIME, menuScene));
			break;
		}
	});

    return true;
}
