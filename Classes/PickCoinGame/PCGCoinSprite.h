#ifndef __PICKCOIN_COIN_H__
#define __PICKCOIN_COIN_H__

#define COIN_SPRITE_TAG "ClickSprite -> PCGCoinSprite"

#include "Universal/ClickSprite.h"
#include "cocos2d.h"

typedef ClickSprite super;

class PCGCoinSprite : public ClickSprite {
  public:
    PCGCoinSprite();
    ~PCGCoinSprite();
    bool init();
    static PCGCoinSprite* create();
    cocos2d::Size getTextureSize();

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif // __PICKCOIN_COIN_H__
