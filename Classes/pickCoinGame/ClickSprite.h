#ifndef __PICKCOIN_COIN_H__
#define __PICKCOIN_COIN_H__

#include "cocos2d.h"

class ClickSprite : public cocos2d::Sprite {
public:
	ClickSprite();
	~ClickSprite();
	static ClickSprite* create(cocos2d::Texture2D *texture);
	bool initWithTexture(cocos2d::Texture2D *texture);
};

#endif // __PICKCOIN_COIN_H__
