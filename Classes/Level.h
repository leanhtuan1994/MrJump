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

	cocos2d::TMXTiledMap	*mapLevel;
	cocos2d::Sprite			*denstinationSprite;

};

#endif // __LEVEL_H__
