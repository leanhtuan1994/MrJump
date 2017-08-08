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

// GET WIDTH OF THE MAP - MAP SIZE ( NUMBER OF TILE * SIZE OF PER TILE)
// COUNT TO 0 -> DESTINATION
float Level::getWidth() {
	return ( (this->mapLevel->getMapSize().width * this->getMapLevel()->getTileSize().width ) - ( this->mapLevel->getTileSize().width * 20));
}


void Level::addDestination(cocos2d::Layer *layer) {
	this->destinationSprite = cocos2d::Sprite::create("destination.png");

	TMXObjectGroup *playerObjects = mapLevel->getObjectGroup("playerObjects");
	auto denstinationObject = playerObjects->getObject("destination");

	if (!denstinationObject.empty()) {
		destinationSprite->setPositionX(denstinationObject["x"].asInt());
		destinationSprite->setPositionY(denstinationObject["y"].asInt());
	}

	destinationSprite->setScale(0.5f);
	layer->addChild(destinationSprite, TAG_ZORDER::PLAYER); 
}


