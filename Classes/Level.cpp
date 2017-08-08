#include "Level.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Level::Level() {

}

Level::~Level() {
	mapLevel->release();
}

void Level::loadMap(const char * mapName) {
	mapLevel = cocos2d::TMXTiledMap::create(mapName);
	mapLevel->retain();
}


cocos2d::TMXTiledMap* Level::getMapLevel() {
	return this->mapLevel;
}

float Level::getWidth() {
	return ( (this->mapLevel->getMapSize().width * this->getMapLevel()->getTileSize().width ) - ( this->mapLevel->getTileSize().width * 20));
}

void Level::addDestination(cocos2d::Layer *layer) {
	this->denstinationSprite = cocos2d::Sprite::create("destination.png");

	TMXObjectGroup *playerObjects = mapLevel->getObjectGroup("playerObjects");
	auto denstinationObject = playerObjects->getObject("destination");

	if (!denstinationObject.empty()) {
		denstinationSprite->setPositionX(denstinationObject["x"].asInt());
		denstinationSprite->setPositionY(denstinationObject["y"].asInt());
	}

	denstinationSprite->setScale(0.5f);
	layer->addChild(denstinationSprite, TAG_ZORDER::PLAYER); 
}


