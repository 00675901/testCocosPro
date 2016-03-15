#include "PlayerSprite.h"

USING_NS_CC;
using namespace ccUniversal;

PlayerSprite::PlayerSprite() {
	log("%s new\n", PLAYER_SPRITE_TAG);
}
PlayerSprite::~PlayerSprite() {
	log("%s release\n", PLAYER_SPRITE_TAG);
}
PlayerSprite* PlayerSprite::create() {
	PlayerSprite* pSprite = new PlayerSprite();
	if (pSprite->init()) {
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return nullptr;
}

bool PlayerSprite::init() {
	Texture2D * texture = Director::getInstance()->getTextureCache()->addImage("HelloWorld.png");
	if (texture) {
		if (super::initWithTexture(texture)) {
			name = "YOU";
			return true;
		} else {
			return false;
		}
		return true;
	} else {
		return false;
	}
}

bool PlayerSprite::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) { return false; }
void PlayerSprite::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {}
void PlayerSprite::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {}

Size PlayerSprite::getTextureSize() {
	Texture2D * texture = Director::getInstance()->getTextureCache()->getTextureForKey("HelloWorld.png");
	if (texture) {
		return texture->getContentSize();
	} else {
		return Size(0, 0);
	}
}