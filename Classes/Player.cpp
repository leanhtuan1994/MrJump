#include "Player.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Player::Player() {

}

Player::~Player() {
	
}


Player * Player::create() {
	Player* playerNode = (Player *)CSLoader::createNode("Player.csb");

	cocostudio::timeline::ActionTimeline *actionTimeline = CSLoader::createTimeline("Player.csb");
	playerNode->runAction(actionTimeline);
	actionTimeline->gotoFrameAndPlay(0, true);

	return playerNode;
}


