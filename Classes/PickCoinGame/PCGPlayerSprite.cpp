#include "PCGPlayerSprite.h"

USING_NS_CC;

PCGPlayerSprite::PCGPlayerSprite() {
	log("%s new\n", PCGPLAYER_SPRITE_TAG);
}
PCGPlayerSprite::~PCGPlayerSprite() {
	log("%s release\n", PCGPLAYER_SPRITE_TAG);
}
PCGPlayerSprite* PCGPlayerSprite::create(std::string name, Texture2D* texture) {
	PCGPlayerSprite* pSprite = new PCGPlayerSprite();
	if (pSprite->init(name, texture)) {
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return nullptr;
}

bool PCGPlayerSprite::init(std::string name, Texture2D* texture) {
	if (texture) {
		if (PlayerSprite::initWithTexture(texture)) {
			name = name;
			return true;
		} else {
			return false;
		}
		return true;
	} else {
		return false;
	}
}

bool PCGPlayerSprite::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) { return false; }
void PCGPlayerSprite::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {}
void PCGPlayerSprite::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {}

Size PCGPlayerSprite::getPlayerSize() {
	if (this->texture) {
		return this->texture->getContentSize();
	} else {
		return Size(0, 0);
	}
}