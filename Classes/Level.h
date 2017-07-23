#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"

class Level : public cocos2d::Object
{
public:

	Level();
	virtual ~Level();

	// load map from data file tiled 
	void loadMap(const char * mapName);

	cocos2d::TMXTiledMap* getMapLevel();

	cocos2d::TMXTiledMap *mapLevel;

};

#endif // __LEVEL_H__
