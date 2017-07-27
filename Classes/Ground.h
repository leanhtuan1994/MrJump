#ifndef __GROUND_H__
#define __GROUND_H__

#include "cocos2d.h"

class Ground 
{
public:

	Ground();
	virtual ~Ground();

	std::vector<cocos2d::Node *> listGrounds;

	void getGroundDataInLevel(cocos2d::TMXTiledMap *map);
	
	void addGroundInScene(cocos2d::Layer *layer);

};

#endif // __GROUND_H__
