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
	return (this->mapLevel->getMapSize().width * this->getMapLevel()->getTileSize().width );
}


