#include "MainMenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

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


	// Get tap to play 
	tapTopPlay = (Sprite *)rootNode->getChildByName("spriteTapTopPlay");
	


	this->scheduleUpdate();

    return true;
}


void MainMenuScene::update(float delta) {

	// Update Opacity for taptopplay sprite 
	if (tapTopPlay->getOpacity() <= 0) tapOpacity = 1;
	else if (tapTopPlay->getOpacity() >= 255) tapOpacity = -1;
	tapTopPlay->setOpacity(tapTopPlay->getOpacity() + tapOpacity);


}