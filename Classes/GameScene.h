#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Level.h"	  
#include "MrJump.h"
#include "Ground.h"	 
#include "Sea.h"
#include "Hazard.h"



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


	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void onContactSeparate(cocos2d::PhysicsContact &contact);

	void addGameOverLayer();

	void setStatusMrJumpDie();

private:

	cocos2d::PhysicsWorld*	sceneWorld;
	void setPhysicsWorld(cocos2d::PhysicsWorld* newWorld) {
		this->sceneWorld = newWorld;
	}

	void stopJump(float dt);

	int currentLevelSelected;

	/* Objects in game */
	Level	*level;
	MrJump	*mrJump;
	Ground	*ground;
	Sea		*sea;
	Hazard	*hazard;


	cocos2d::Node *edgeNode;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	// create camera 
	cocos2d::Follow *camera;
	cocos2d::Sprite *cameraTarget;

	// listener 
	cocos2d::EventListenerTouchOneByOne *touchListener;
	cocos2d::EventListenerPhysicsContact *contactListener;


	float limitedCameraPositionX;
	float spaceCameraPositionX;

	/* user data */
	cocos2d::UserDefault *userDafault;

	// get time when touch began 
	long long timeTouchBegan;
	
	// check time over to stop jumping 
	bool isTouchTimeForJump;

	int soundLevelID;

	/* counting number of jump */
	int numberJumped;

	int percentWidthOfMrJump;

};

#endif // __GAME_SCENE_H__
