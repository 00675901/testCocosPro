#include "PlayerLayer.h"

USING_NS_CC;
using namespace ccUniversal;

PlayerLayer::~PlayerLayer() {
	log("Pick_Coin_Game release\n");
}

bool PlayerLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	return true;
}