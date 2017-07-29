#include "MainMenuScene.h"
#include "LevelSelectionScene.h"
#include "Definitions.h"
#include "SettingScene.h"

#include "cocostudio/CocoStudio.h"

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
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainMenuScene.csb");

	
	// Run animation
	cocostudio::timeline::ActionTimeline *actionTimeline = CSLoader::createTimeline("MainMenuScene.csb");
	rootNode->runAction(actionTimeline);
	actionTimeline->gotoFrameAndPlay(0, true);

    addChild(rootNode);


	/* Button Setting listener */
	btnSetting = (cocos2d::ui::Button *) rootNode->getChildByName("btnSetting");
	btnSetting->addTouchEventListener([](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			auto scene = SettingScene::createScene();
			Director::getInstance()->replaceScene(TransitionMoveInL::create(TRANSITION_TIME, scene));
			break;
		}
	});

	// Get tap to play 
	tapTopPlay = (Sprite *)rootNode->getChildByName("spriteTapTopPlay");
	// Create a one by one touch event listener 
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainMenuScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

    return true;
}


void MainMenuScene::update(float delta) {

	// Update Opacity for taptopplay sprite 
	if (tapTopPlay->getOpacity() <= 0) tapOpacity = 1;
	else if (tapTopPlay->getOpacity() >= 255) tapOpacity = -1;
	tapTopPlay->setOpacity(tapTopPlay->getOpacity() + tapOpacity);


}

bool MainMenuScene::onTouchBegan(Touch *touch, Event *unused_event) {
	gotoLevelSelectionScene();
	return true;
}

void MainMenuScene::gotoLevelSelectionScene() {
	auto scene = LevelSelectionScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInR::create(TRANSITION_TIME_MOVE_IN_R, scene));
}
