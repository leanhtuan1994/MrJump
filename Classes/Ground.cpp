#include "Ground.h"
#include "Definitions.h"

USING_NS_CC;

Ground::Ground() {

}

Ground::~Ground() {

}


void Ground::getGroundDataInLevel(cocos2d::TMXTiledMap *map) {
	/* get player object in level tiled map */
	TMXObjectGroup *groundGroup = map->getObjectGroup("groundObjects");
	auto grounds = groundGroup->getObjects();
	int sizeGrounds = grounds.size();

	/* get objects and set physics body for it */
	for (int i = 0; i < sizeGrounds; i++) {
		// Create Node Object 
		auto groudNode = cocos2d::Node::create();
		groudNode->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
		groudNode->setContentSize(cocos2d::Size(grounds[i].asValueMap()["width"].asInt(), grounds[i].asValueMap()["height"].asInt()));
		groudNode->setPosition(cocos2d::Vec2(grounds[i].asValueMap()["x"].asInt(), grounds[i].asValueMap()["y"].asInt()));

		// Create Physics body 
		auto groudBody = cocos2d::PhysicsBody::createBox(groudNode->getContentSize(), cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
		groudBody->setDynamic(false);
		groudBody->setCollisionBitmask(GROUND_COLLISION_BITMASK);
		groudBody->setContactTestBitmask(true);
		groudBody->setLinearDamping(1.0f);
		

		// Added physics body to node and add to list node 
		groudNode->setPhysicsBody(groudBody);
		groudNode->retain();
		listGrounds.push_back(groudNode);
	}
}


void Ground::addGroundInScene(cocos2d::Layer *layer) {
	int sizeGrounds = listGrounds.size();

	for (int i = 0; i < sizeGrounds; i++) {
		layer->addChild(listGrounds.at(i));
	}
}