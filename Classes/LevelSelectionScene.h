#ifndef __LEVE_SELECTION_SCENE_H__
#define __LEVE_SELECTION_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


class LevelSelectionScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(LevelSelectionScene);


private:
	
	/* ui objects in the scene */
	cocos2d::ui::PageView	*pageView;
	cocos2d::ui::Layout		*panelLevel1;
	cocos2d::ui::Button		*btnCloseScene;
	cocos2d::ui::Text		*lblHighestScore;

};

#endif // __LEVE_SELECTION_SCENE_H__
