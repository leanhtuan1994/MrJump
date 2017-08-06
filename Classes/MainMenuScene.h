#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class MainMenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(MainMenuScene);

	void update(float delta);


	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	void gotoLevelSelectionScene();

	void setMusicEffect();

private:

	int tapOpacity = 0;


	cocos2d::Sprite			*tapTopPlay;
	cocos2d::ui::Button		*btnSetting;
	cocos2d::ui::Button		*btnLevelWorld;


	cocos2d::UserDefault	*userdefault;
	int isPlayBackgroundMusic;
	int isPlayAudioEffect;
};

#endif // __MAIN_MENU_SCENE_H__
