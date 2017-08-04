#ifndef __HAZARD_H__
#define __HAZARD_H__

#include "cocos2d.h"

class Hazard
{
public:

	Hazard();
	virtual ~Hazard();

	std::vector<cocos2d::Node *> listHazards;

	void getHazardDataInLevel(cocos2d::TMXTiledMap *map);
	
	void addHazardInScene(cocos2d::Layer *layer);

};

#endif // __HAZARD_H__
