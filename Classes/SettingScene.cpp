#include "SettingScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

#define CHILD_NAME_BUTTON_BACKGROUNDMUSIC			"btnBackgroundMusic" 
#define CHILD_NAME_BUTTON_AUDIOEFFECT				"btnAudioEffect"


#define BUTTON_BACKGROUND_MUSIC_NORMAL_TURNON		"assets/SoundBackgroundButtonNormal.png"
#define BUTTON_BACKGROUND_MUSIC_SELECTED_TURNON		"assets/SoundBackgroundButtonSelected.png"
#define BUTTON_BACKGROUND_MUSIC_NORMAL_TURNOFF		"assets/SoundBackgroundButtonNormal_TurnOff.png"
#define BUTTON_BACKGROUND_MUSIC_SELECTED_TURNOFF	"assets/SoundBackgroundButtonSelected_TurnOff.png"


#define BUTTON_AUDIO_EFFECT_NORMAL_TURNON			"assets/ButtonSoundSelected.png"
#define BUTTON_AUDIO_EFFECT_SELECTED_TURNON			"assets/ButtonSoundNormal.png"
#define BUTTON_AUDIO_EFFECT_NORMAL_TURNOFF			"assets/ButtonSoundSelected_TurnOff.png"
#define BUTTON_AUDIO_EFFECT_SELECTED_TURNOFF		"assets/ButtonSoundNormal_TurnOff.png"





USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SettingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = SettingScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SettingScene::init()
{
    
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ) {
        return false;
    }
    
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	this->isButtonBackgroundMusicStatusChange = false;
	this->isButtonAudioEffectStatusChange = false;


    auto rootNode = CSLoader::createNode("SettingScene.csb");
    addChild(rootNode);

	btnCloseSetting = (cocos2d::ui::Button *) rootNode->getChildByName("btnCloseSetting");
	btnBackgroundMusic = (cocos2d::ui::Button *) rootNode->getChildByName(CHILD_NAME_BUTTON_BACKGROUNDMUSIC);
	btnAudioEffect = (cocos2d::ui::Button *) rootNode->getChildByName(CHILD_NAME_BUTTON_AUDIOEFFECT);


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	int isPlayBackgroundMusic = UserDefault::getInstance()->getIntegerForKey(USER_DATA_KEY_IS_PLAY_BACKGROUND_MUSIC);
	if (isPlayBackgroundMusic == USER_SETUP_AUDIO::TURN_ON ) {
		btnBackgroundMusic->loadTextureNormal(BUTTON_BACKGROUND_MUSIC_NORMAL_TURNON);
		btnBackgroundMusic->loadTexturePressed(BUTTON_BACKGROUND_MUSIC_SELECTED_TURNON);
	} else {
		btnBackgroundMusic->loadTextureNormal(BUTTON_BACKGROUND_MUSIC_NORMAL_TURNOFF);
		btnBackgroundMusic->loadTexturePressed(BUTTON_BACKGROUND_MUSIC_SELECTED_TURNOFF);
	}

	/************************************************************************/
	/*                                                                      */
	/************************************************************************/

	int isAudioEffect = UserDefault::getInstance()->getIntegerForKey(USER_DATA_KEY_IS_PLAY_AUDIO_EFFECT);
	if (isAudioEffect == USER_SETUP_AUDIO::TURN_ON) {
		btnAudioEffect->loadTextureNormal(BUTTON_AUDIO_EFFECT_NORMAL_TURNON);
		btnAudioEffect->loadTexturePressed(BUTTON_AUDIO_EFFECT_SELECTED_TURNON);
	} else {
		btnAudioEffect->loadTextureNormal(BUTTON_AUDIO_EFFECT_NORMAL_TURNOFF);
		btnAudioEffect->loadTexturePressed(BUTTON_AUDIO_EFFECT_SELECTED_TURNOFF);
	}
					    

	btnBackgroundMusic->addTouchEventListener(CC_CALLBACK_2(SettingScene::onButtonBackgroundMusicTouchEvent, this));
	btnAudioEffect->addTouchEventListener(CC_CALLBACK_2(SettingScene::onButtonAudioEffectTouchEvent, this));


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	btnCloseSetting->addTouchEventListener([](cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type) {
		switch (type) {
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			// goto MainMenuScene
			auto scene = MainMenuScene::createScene();
			Director::getInstance()->replaceScene(TransitionMoveInR::create(TRANSITION_TIME_MOVE_IN_R, scene));
			break;
		}
	});


	this->scheduleUpdate();

    return true;
}

void SettingScene::onButtonBackgroundMusicTouchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
	switch (type) {
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		isButtonBackgroundMusicStatusChange = true;

		int isPlayBackgroundMusic = UserDefault::getInstance()->getIntegerForKey(USER_DATA_KEY_IS_PLAY_BACKGROUND_MUSIC);
		if (isPlayBackgroundMusic == USER_SETUP_AUDIO::TURN_ON) {
			if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
				CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			}
			UserDefault::getInstance()->setIntegerForKey(USER_DATA_KEY_IS_PLAY_BACKGROUND_MUSIC, USER_SETUP_AUDIO::TURN_OFF);

		} else {
			if (!CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
				CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(FILEPATH_BACKGROUND_MUSIC, true);
			}
			UserDefault::getInstance()->setIntegerForKey(USER_DATA_KEY_IS_PLAY_BACKGROUND_MUSIC, USER_SETUP_AUDIO::TURN_ON);

		}
		break;
	}
}

void SettingScene::onButtonAudioEffectTouchEvent(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
	switch (type) {
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		isButtonAudioEffectStatusChange = true;
		int isPlayAudioEfefct = UserDefault::getInstance()->getIntegerForKey(USER_DATA_KEY_IS_PLAY_AUDIO_EFFECT);
		if (isPlayAudioEfefct == TURN_ON) {
			UserDefault::getInstance()->setIntegerForKey(USER_DATA_KEY_IS_PLAY_AUDIO_EFFECT, TURN_OFF);
		} else {
			UserDefault::getInstance()->setIntegerForKey(USER_DATA_KEY_IS_PLAY_AUDIO_EFFECT, TURN_ON);
		}
		break;
	}
}



void SettingScene::update(float dt) {
	if (this->isButtonBackgroundMusicStatusChange ) {
		int isPlayBackgroundMusic = UserDefault::getInstance()->getIntegerForKey(USER_DATA_KEY_IS_PLAY_BACKGROUND_MUSIC);
		if (isPlayBackgroundMusic == USER_SETUP_AUDIO::TURN_ON) {
			btnBackgroundMusic->loadTextureNormal(BUTTON_BACKGROUND_MUSIC_NORMAL_TURNON);
			btnBackgroundMusic->loadTexturePressed(BUTTON_BACKGROUND_MUSIC_SELECTED_TURNON);
		} else {
			btnBackgroundMusic->loadTextureNormal(BUTTON_BACKGROUND_MUSIC_NORMAL_TURNOFF);
			btnBackgroundMusic->loadTexturePressed(BUTTON_BACKGROUND_MUSIC_SELECTED_TURNOFF);
		}
		isButtonBackgroundMusicStatusChange = false;
	}


	if (isButtonAudioEffectStatusChange) {
		int isAudioEffect = UserDefault::getInstance()->getIntegerForKey(USER_DATA_KEY_IS_PLAY_AUDIO_EFFECT);
		if (isAudioEffect == USER_SETUP_AUDIO::TURN_ON) {
			btnAudioEffect->loadTextureNormal(BUTTON_AUDIO_EFFECT_NORMAL_TURNON);
			btnAudioEffect->loadTexturePressed(BUTTON_AUDIO_EFFECT_SELECTED_TURNON);
		} else {
			btnAudioEffect->loadTextureNormal(BUTTON_AUDIO_EFFECT_NORMAL_TURNOFF);
			btnAudioEffect->loadTexturePressed(BUTTON_AUDIO_EFFECT_SELECTED_TURNOFF);
		}
		isButtonAudioEffectStatusChange = false;
	}
}