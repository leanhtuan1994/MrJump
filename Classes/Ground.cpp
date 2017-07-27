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
	for (int i = 0; i < grounds.size(); i++) {
		auto groudNode = cocos2d::Node::create();
		groudNode->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
		groudNode->setContentSize(cocos2d::Size(grounds[i].asValueMap()["width"].asInt(), grounds[i].asValueMap()["height"].asInt()));
		groudNode->setPosition(cocos2d::Vec2(grounds[i].asValueMap()["x"].asInt(), grounds[i].asValueMap()["y"].asInt()));

		auto groudBody = cocos2d::PhysicsBody::createBox(groudNode->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

		groudBody->setDynamic(false);
		groudNode->setPhysicsBody(groudBody);

		listGrounds.push_back(groudNode);
	}
}


void Ground::addGroundInScene(cocos2d::Layer *layer) {
	int sizeGrounds = listGrounds.size();

	for (int i = 0; i < sizeGrounds; i++) {
		layer->addChild(listGrounds.at(i));
	}
}