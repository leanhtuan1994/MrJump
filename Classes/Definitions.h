#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__


#define TRANSITION_TIME					0.2f
#define TRANSITION_TIME_MOVE_IN_R		0.2f
#define TRANSITION_TIME_GAME_OVER		0.1f

#define DISPLAY_TIME_SPLASH_SCENE		0.2f

#define TIME_TOUCH_JUMP					245


#define NUM_FRAME_ANIMATION_JUMP		16
#define ANIMATION_DELAY_TIME_JUMP		0.05f


#define MRJUMP_RUNNING_SPEED			5.7f
#define MRJUMP_JUMPING_DUARATION		0.25f


#define MRJUMP_COLLISION_BITMASK		0x0001
#define GROUND_COLLISION_BITMASK		0x0002
#define HAZARD_COLLISION_BITMASK		0x0003

#define MUSIC_EFFECT_LEVEL_TURN_OFF		-1


#define FILEPATH_BACKGROUND_MUSIC		"Mr_Jump_Background.wav"
#define FILEPATH_LEVEL_MUSIC_EFFECT		"Mr_Jump_Music_Level_1.wav"


#define USER_DATA_KEY_MUSIC_EFFECT		"USERDATAKEYMUSICEFFECT"
#define USER_DATA_KEY_SCORE_PERCENT		"USERDATAKEYSCOREPERCENT"
#define USER_DATA_KEY_NUMBER_JUMPS		"USERDATAKEYNUMBERJUMPS"



enum LEVEL_NAME {
	LEVEL_1 = 1,
	LEVEL_2
};

enum TAG_ZORDER {
	UI, 
	MAP,
	PLAYER,
	GAMEOVERLAYER
};




#endif // __DEFINITIONS_H__
