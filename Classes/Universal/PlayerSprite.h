#ifndef __UNIVERSAL_PLAYER_SPRITE_H__
#define __UNIVERSAL_PLAYER_SPRITE_H__

#define PLAYER_SPRITE_TAG "ClickSprite -> PlayerSprite"

#include "cocos2d.h"
#include "ClickSprite.h"


namespace ccUniversal {
	typedef ClickSprite super;

	class PlayerSprite : public ClickSprite {
	public:
		PlayerSprite();
		~PlayerSprite();
		bool init();
		static PlayerSprite* create();
		cocos2d::Size getTextureSize();

		bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

		cocos2d::String name;
		int actionCount = 3;

	};
}


#endif // __UNIVERSAL_PLAYER_SPRITE_H__
