#ifndef __SEA_H__
#define __SEA_H__

#include "cocos2d.h"

class Sea 
{
public:

	Sea();
	virtual ~Sea();

	// List to save sea objects
	std::vector<cocos2d::Node *> listSeas;

	// Get Sea OBjects in the level map and save it in list 
	void getSeaDataInLevel(cocos2d::TMXTiledMap *map);
	
	// Add Sea OBjects to layer 
	void addSeaInScene(cocos2d::Layer *layer);

};

#endif // __GROUND_H__
