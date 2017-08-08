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

	float getWidth();

	cocos2d::TMXTiledMap* getMapLevel();

	void addDestination(cocos2d::Layer *layer);

	void actionForDestination();


private:

	// TMX Tiled map designed by Tiled
	cocos2d::TMXTiledMap	*mapLevel;

	// destination sprite in the level map
	cocos2d::Sprite			*destinationSprite;

};

#endif // __LEVEL_H__
