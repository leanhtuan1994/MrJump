#include "Hazard.h"
#include "Definitions.h"


#define TILEDMAP_OBJECT_NAME	"enemyObjects"

USING_NS_CC;

Hazard::Hazard() {

}

Hazard::~Hazard() {

}


void Hazard::getHazardDataInLevel(cocos2d::TMXTiledMap *map) {
	TMXObjectGroup *hazardObjectsInTiledMap = map->getObjectGroup(TILEDMAP_OBJECT_NAME);

	cocos2d::ValueVector hazardObjectsValue = hazardObjectsInTiledMap->getObjects();
	int sizeHazardObjects = hazardObjectsValue.size();

	for (int i = 0; i < sizeHazardObjects; i++) {

		cocos2d::ValueMap hazard = hazardObjectsValue.at(i).asValueMap();

		if (!hazard.empty()) {

			cocos2d::ValueVector hazardPointValues = hazard["points"].asValueVector();

			int sizePoints = hazardPointValues.size();

			Vec2 *points = new Vec2[sizePoints + 1];

			for (int k = 0; k < sizePoints; k++) {
				auto posPoint = hazardPointValues.at(k).asValueMap();
				int x = posPoint["x"].asInt();
				int y = posPoint["y"].asInt();

				points[k].x = x;
				points[k].y = y;
			}

			points[sizePoints].x = points[0].x;
			points[sizePoints].y = points[0].y;

			auto hazardBody = PhysicsBody::createEdgePolygon(points, sizePoints + 1, PHYSICSBODY_MATERIAL_DEFAULT, 2.0F);

			hazardBody->setDynamic(false);
			hazardBody->setCollisionBitmask(HAZARD_COLLISION_BITMASK);
			hazardBody->setContactTestBitmask(true);

			cocos2d::Node *hazardNode = Node::create();
			hazardNode->setPosition(hazard["x"].asInt(), hazard["y"].asInt());
			hazardNode->setPhysicsBody(hazardBody);
			hazardNode->setRotation(180.0f);
			hazardNode->retain();
			
			this->listHazards.push_back(hazardNode);
		}
	}
}


void Hazard::addHazardInScene(cocos2d::Layer *layer) {
	int sizeHazard = listHazards.size();

	for (int i = 0; i < sizeHazard; i++) {
		layer->addChild(listHazards.at(i));
	}
}