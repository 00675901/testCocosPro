#include "PlayerSprite.h"

USING_NS_CC;

PlayerSprite::PlayerSprite() {
    log("%s new\n", PLAYER_SPRITE_TAG);
}
PlayerSprite::~PlayerSprite() {
    log("%s release\n", PLAYER_SPRITE_TAG);
}
PlayerSprite* PlayerSprite::create(Texture2D* texture) {
    PlayerSprite* pSprite = new PlayerSprite();
    if (pSprite->init(texture)) {
        pSprite->autorelease();
        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return nullptr;
}

bool PlayerSprite::init(Texture2D* texture) {
    if (texture) {
        if (ClickSprite::initWithTexture(texture)) {
            name = "Player";
            return true;
        } else {
            return false;
        }
        return true;
    } else {
        return false;
    }
}

bool PlayerSprite::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    return false;
}
void PlayerSprite::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
}
void PlayerSprite::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
}