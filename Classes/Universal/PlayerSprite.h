#ifndef __UNIVERSAL_PLAYER_SPRITE_H__
#define __UNIVERSAL_PLAYER_SPRITE_H__

#define PLAYER_SPRITE_TAG "ClickSprite -> PlayerSprite"

#include "ClickSprite.h"
#include "cocos2d.h"

class PlayerSprite : public ClickSprite {
  public:
    PlayerSprite();
    virtual ~PlayerSprite();
    bool init(cocos2d::Texture2D*);
    static PlayerSprite* create(cocos2d::Texture2D*);

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    std::string name;
    cocos2d::Texture2D* texture;
};

#endif // __UNIVERSAL_PLAYER_SPRITE_H__
