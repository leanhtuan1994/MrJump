#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Level.h"	  
#include "MrJump.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);


	void update(float delta);


private:

	cocos2d::PhysicsWorld*	sceneWorld;
	void setPhysicsWorld(cocos2d::PhysicsWorld* newWorld) {
		this->sceneWorld = newWorld;
	}

	Level *level;
	int currentLevelSelected;

	MrJump *mrJump;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};

#endif // __GAME_SCENE_H__
