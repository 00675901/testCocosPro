#ifndef __PICKCOIN_SCENE_H__
#define __PICKCOIN_SCENE_H__

#include "cocos2d.h"
#include <time.h>
#include "PCGCoinSprite.h"
#include "PCGPlayerLayer.h"

class PickCoinGame : public cocos2d::Layer {
public:
	~PickCoinGame();
	static cocos2d::Scene* createScene();
	bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(PickCoinGame);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void spriteCallback(cocos2d::Sprite* sprite, int actionTag);
private:
	int currCoinCount = 0;
	int maxCoinCount = 30;
	int pickCount = 3;
	bool isAI = true;
	cocos2d::Layer *mainLayer;
	PCGPlayerLayer *playerLayer;
	cocos2d::Vector<cocos2d::Sprite*> spriteCache;
	cocos2d::Map<int, cocos2d::Sprite*> opeSpriteCache;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Rect coinLocalRang;
	cocos2d::Label *countLabel;

	bool initResource();
	bool initSceneUI();
	bool initCoin();
	void setAI(bool);

	int randomCoinCount();
	void randomCoinLocal(cocos2d::Sprite *sprite);
	void operationCoin();
	void operationCoinByAI();
	void reloadCoin();
};



#endif // __HELLOWORLD_SCENE_H__
