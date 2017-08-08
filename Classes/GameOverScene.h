#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


class GameOverScene : public cocos2d::Layer
{
public:

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(GameOverScene);


private:

	// UI OF THE SCENE 
	cocos2d::ui::Button		*btnPlayAgain;
	cocos2d::ui::Button		*btnCloseLayer;
	cocos2d::ui::Text		*lblScorePercent;
	cocos2d::ui::Text		*lblNumberJumps;


	cocos2d::UserDefault	*userDefault;

	// GET HIGHEST SCORE IN USER DATA
	int highestScorePercent;

};

#endif // __GAME_OVER_SCENE_H__
