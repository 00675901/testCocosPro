#ifndef __PICKCOIN_COIN_H__
#define __PICKCOIN_COIN_H__

#define COIN_SPRITE_TAG "ClickSprite -> CoinSprite"

#include "cocos2d.h"
#include <Universal/ClickSprite.h>

namespace ccPickCoinGame {
	typedef ccUniversal::ClickSprite super;

	class CoinSprite : public ccUniversal::ClickSprite {
	public:

		CoinSprite();
		~CoinSprite();
		bool init();
		static CoinSprite* create();
		cocos2d::Size getTextureSize();

		bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	};
}



#endif // __PICKCOIN_COIN_H__
