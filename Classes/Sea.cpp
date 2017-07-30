#include "Sea.h"
#include "Definitions.h"

USING_NS_CC;

Sea::Sea() {

}

Sea::~Sea() {
	
}


void Sea::getSeaDataInLevel(cocos2d::TMXTiledMap *map) {
	/* get player object in level tiled map */
	TMXObjectGroup *seaGroup = map->getObjectGroup("seaObjects");
	auto seas = seaGroup->getObjects();
	int sizeSeas = seas.size();

	/* get objects and set physics body for it */
	for (int i = 0; i < sizeSeas; i++) {
		// Create Node Object 
		auto seaNode = cocos2d::Node::create();
		seaNode->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
		seaNode->setContentSize(cocos2d::Size(seas[i].asValueMap()["width"].asInt(), seas[i].asValueMap()["height"].asInt()));
		seaNode->setPosition(cocos2d::Vec2(seas[i].asValueMap()["x"].asInt(), seas[i].asValueMap()["y"].asInt()));

		// Create Physics body 
		auto seaBody = cocos2d::PhysicsBody::createBox(seaNode->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
		seaBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
		seaBody->setContactTestBitmask(true);
		seaBody->setDynamic(false);

		// Added physics body to node and add to list node 
		seaNode->setPhysicsBody(seaBody);

		seaNode->retain();

		listSeas.push_back(seaNode);
	}
}


void Sea::addSeaInScene(cocos2d::Layer *layer) {
	int sizeSeas = listSeas.size();

	for (int i = 0; i < sizeSeas; i++) {
		layer->addChild(listSeas.at(i));
	}
}