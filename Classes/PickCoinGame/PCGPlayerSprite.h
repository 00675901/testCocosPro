#ifndef __PICKCOIN_PLAYER_SPRITE_H__
#define __PICKCOIN_PLAYER_SPRITE_H__

#define PCGPLAYER_SPRITE_TAG "ClickSprite -> PlayerSprite -> PCGPlayerSprite"

#include "cocos2d.h"
#include "Universal/PlayerSprite.h"

class PCGPlayerSprite : public PlayerSprite {
public:
	PCGPlayerSprite();
	virtual ~PCGPlayerSprite();
	bool init(std::string, cocos2d::Texture2D*);
	static PCGPlayerSprite* create(std::string, cocos2d::Texture2D*);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	cocos2d::Size getPlayerSize();

	int actionCount = 3;
	int repeatCount = 0;
	int preNum = 0;
};


#endif // __UNIVERSAL_PLAYER_SPRITE_H__
