#ifndef __PICKCOIN_CLICKSPRITE_H__
#define __PICKCOIN_CLICKSPRITE_H__

#include "cocos2d.h"

#define CLICK_SPRITE_TAG "ClickSprite"

typedef std::function<void(cocos2d::Ref*)> clickSpriteCallback;

class ClickSprite : public cocos2d::Sprite {
public:
	ClickSprite();
	virtual ~ClickSprite();
	static ClickSprite* create(cocos2d::Texture2D *texture);
	bool initWithTexture(cocos2d::Texture2D *texture);
	// callback
	clickSpriteCallback _callback;
	void setCallback(const clickSpriteCallback& callback);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
protected:
	cocos2d::EventListenerTouchOneByOne *listener;
};

#endif // __PICKCOIN_CLICKPRITE_H__
