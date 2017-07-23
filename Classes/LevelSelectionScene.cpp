#include "LevelSelectionScene.h"
#include "GameScene.h"
#include "Definitions.h"
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
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("LevelSelectionScene.csb");
    addChild(rootNode);

	// PageView cast to a PageView using it's name
	pageView = (cocos2d::ui::PageView *)rootNode->getChildByName("PageView_LevelSelection");
	panelLevel1 = (cocos2d::ui::Layout *) pageView->getChildByName("Panel_Level_1");

	panelLevel1->addTouchEventListener([](Ref * sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			auto userdefault = UserDefault::getInstance();
			userdefault->setIntegerForKey("Level", 1);
			Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, GameScene::createScene()));
			break;
		}
	});



    return true;
}


void LevelSelectionScene::gotoGameScene() {
	
}