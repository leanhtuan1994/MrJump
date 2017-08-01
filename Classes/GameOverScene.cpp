#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
USING_NS_CC;



// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	/* Add node from cocos studio */
	auto rootNode = CSLoader::createNode("GameOverLayer.csb");

	// Run animation
	cocostudio::timeline::ActionTimeline *actionTimeline = CSLoader::createTimeline("GameOverLayer.csb");
	rootNode->runAction(actionTimeline);
	actionTimeline->gotoFrameAndPlay(0, false);

	this->addChild(rootNode);


	/* Get btnPlayAgain and Add touch listener */
	btnPlayAgain = (cocos2d::ui::Button *) rootNode->getChildByName("btnPlayAgain");
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


	/* */
	btnCloseLayer = (cocos2d::ui::Button *) rootNode->getChildByName("btnCloseLayer");
	btnCloseLayer->addTouchEventListener([](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			auto menuScene = MainMenuScene::createScene();
			cocos2d::Director::getInstance()->replaceScene(TransitionMoveInL::create(TRANSITION_TIME, menuScene));
			break;
		}
	});

    return true;
}
