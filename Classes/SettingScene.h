#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


class SettingScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(SettingScene);

	// Listener  touch event for Button Background Music 
	void onButtonBackgroundMusicTouchEvent( cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	// Listener  touch event for Button Music Effect
	void onButtonAudioEffectTouchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	// Listener  touch event for Button Close Scene
	void onButtonCloseSceneTouchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	// update scene for every frame
	void update(float dt);

private:
	
	// UI Button Object 
	cocos2d::ui::Button *btnCloseSetting;
	cocos2d::ui::Button *btnBackgroundMusic;
	cocos2d::ui::Button *btnAudioEffect;

	// flag to listen touch event 
	bool isButtonBackgroundMusicStatusChange;
	bool isButtonAudioEffectStatusChange;
};

#endif // __SETTING_SCENE_H__
