#include "Hazard.h"
#include "Definitions.h"


#define TILEDMAP_OBJECT_NAME	"enemyObjects"

USING_NS_CC;

Hazard::Hazard() {

}

Hazard::~Hazard() {

}


/************************************************************************/
/*        GET OBJECTS IN THE LEVEL MAP AND SAVE IN THE LIST HAZARD                                                              
/************************************************************************/
void Hazard::getHazardDataInLevel(cocos2d::TMXTiledMap *map) {
	// Get ObjectGround in Level Map 
	TMXObjectGroup *hazardObjectsInTiledMap = map->getObjectGroup(TILEDMAP_OBJECT_NAME);

	// Convert Objects to Value Vector 
	cocos2d::ValueVector hazardObjectsValue = hazardObjectsInTiledMap->getObjects();
	int sizeHazardObjects = hazardObjectsValue.size();

	// Get Value Object 
	for (int i = 0; i < sizeHazardObjects; i++) {

		// Convert value of object to value map 
		cocos2d::ValueMap hazard = hazardObjectsValue.at(i).asValueMap();

		if (!hazard.empty()) {

			// Get Points of this object.
			cocos2d::ValueVector hazardPointValues = hazard["points"].asValueVector();
			int sizePoints = hazardPointValues.size();

			// Create points poiter to save point in this objects
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

			// Create physics body 
			auto hazardBody = PhysicsBody::createEdgePolygon(points, sizePoints + 1, PHYSICSBODY_MATERIAL_DEFAULT, 2.0F);
			hazardBody->setDynamic(false);
			hazardBody->setCollisionBitmask(HAZARD_COLLISION_BITMASK);
			hazardBody->setContactTestBitmask(true);

			// Create node object and set physics body for it
			cocos2d::Node *hazardNode = Node::create();
			hazardNode->setPosition(hazard["x"].asInt(), hazard["y"].asInt());
			hazardNode->setPhysicsBody(hazardBody);
			hazardNode->setRotation(180.0f);
			hazardNode->retain();
			
			// Push in list hazard
			this->listHazards.push_back(hazardNode);
		}
	}
}


/************************************************************************/
/*                 ADD LIST HAZARD INTO LAYER 
/************************************************************************/
void Hazard::addHazardInScene(cocos2d::Layer *layer) {
	int sizeHazard = listHazards.size();

	for (int i = 0; i < sizeHazard; i++) {
		layer->addChild(listHazards.at(i));
	}
}