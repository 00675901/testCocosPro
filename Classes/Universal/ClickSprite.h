#ifndef __UNIVERSAL_CLICK_SPRITE_H__
#define __UNIVERSAL_CLICK_SPRITE_H__

#include "cocos2d.h"

#define CLICK_SPRITE_TAG "ClickSprite"
namespace ccUniversal {
	typedef std::function<void(cocos2d::Sprite*, int)> clickSpriteCallback;

	class ClickSprite : public cocos2d::Sprite {
	public:
		ClickSprite();
		virtual ~ClickSprite();
		static ClickSprite* create(cocos2d::Texture2D *texture);
		bool initWithTexture(cocos2d::Texture2D *texture);
		// callback
		clickSpriteCallback _callback;
		void setCallback(const clickSpriteCallback& callback);
		void clickSpriteCallBack(int actionTag);

		virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
		virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
		virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	protected:
		cocos2d::EventListenerTouchOneByOne *listener;
	};
}
#endif // __UNIVERSAL_CLICK_SPRITE_H__
