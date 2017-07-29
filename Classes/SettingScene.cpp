#include "SettingScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SettingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = SettingScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SettingScene::init()
{
    
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("SettingScene.csb");
    addChild(rootNode);


	/* Button Close Setting */
	btnCloseSetting = (cocos2d::ui::Button *) rootNode->getChildByName("btnCloseSetting");
	btnCloseSetting->addTouchEventListener([](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			// goto MainMenuScene
			auto scene = MainMenuScene::createScene();
			Director::getInstance()->replaceScene(TransitionMoveInR::create(TRANSITION_TIME_MOVE_IN_R, scene));
			break;
		}
	});


    return true;
}