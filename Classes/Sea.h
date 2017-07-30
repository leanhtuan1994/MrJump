#ifndef __SEA_H__
#define __SEA_H__

#include "cocos2d.h"

class Sea 
{
public:

	Sea();
	virtual ~Sea();

	std::vector<cocos2d::Node *> listSeas;

	void getSeaDataInLevel(cocos2d::TMXTiledMap *map);
	
	void addSeaInScene(cocos2d::Layer *layer);

};

#endif // __GROUND_H__
