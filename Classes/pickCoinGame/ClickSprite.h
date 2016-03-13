#ifndef __PICKCOIN_COIN_H__
#define __PICKCOIN_COIN_H__

#include "cocos2d.h"

typedef std::function<void(cocos2d::Ref*)> clickSpriteCallback;

class ClickSprite : public cocos2d::Sprite {
public:
	ClickSprite();
	~ClickSprite();
	static ClickSprite* create(cocos2d::Texture2D *texture);
	bool initWithTexture(cocos2d::Texture2D *texture);
    // callback
    clickSpriteCallback _callback;
    void setCallback(const clickSpriteCallback& callback);
private:
    cocos2d::EventListenerTouchOneByOne *listener;
};

#endif // __PICKCOIN_COIN_H__
