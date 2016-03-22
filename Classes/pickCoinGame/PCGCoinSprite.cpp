#include "PCGCoinSprite.h"

USING_NS_CC;

PCGCoinSprite::PCGCoinSprite() {
    log("%s new\n", COIN_SPRITE_TAG);
}
PCGCoinSprite::~PCGCoinSprite() {
    log("%s release\n", COIN_SPRITE_TAG);
}
PCGCoinSprite* PCGCoinSprite::create() {
    PCGCoinSprite* pSprite = new PCGCoinSprite();
    if (pSprite->init()) {
        pSprite->autorelease();
        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return nullptr;
}

bool PCGCoinSprite::init() {
    Texture2D* texture = Director::getInstance()->getTextureCache()->getTextureForKey("testCoin.png");
    if (texture) {
        if (super::initWithTexture(texture)) {
            return true;
        } else {
            return false;
        }
        return true;
    } else {
        return false;
    }
}

bool PCGCoinSprite::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (super::onTouchBegan(touch, event)) {
        //log("%s onTouchBegan", COIN_SPRITE_TAG);
        clickSpriteCallBack(0);
        return true;
    } else {
        return false;
    }
}
void PCGCoinSprite::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    super::onTouchMoved(touch, event);
    //log("%s onTouchMoved", COIN_SPRITE_TAG);
}
void PCGCoinSprite::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    super::onTouchEnded(touch, event);
    //log("%s onTouchEnded", COIN_SPRITE_TAG);
}

Size PCGCoinSprite::getTextureSize() {
    Texture2D* texture = Director::getInstance()->getTextureCache()->getTextureForKey("testCoin.png");
    if (texture) {
        return texture->getContentSize();
    } else {
        return Size(0, 0);
    }
}