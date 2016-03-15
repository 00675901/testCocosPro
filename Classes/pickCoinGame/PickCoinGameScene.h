#ifndef __PICKCOIN_SCENE_H__
#define __PICKCOIN_SCENE_H__

#include "cocos2d.h"
#include <time.h>
#include "CoinSprite.h"
#include <Libs/GUtils.h>

namespace ccPickCoinGame {
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
		cocos2d::Layer *mainLayer;
		cocos2d::Vector<cocos2d::Sprite*> spriteCache;
		cocos2d::Map<int, cocos2d::Sprite*> opeSpriteCache;
		cocos2d::Size visibleSize;
		cocos2d::Vec2 origin;
		cocos2d::Rect coinLocalRang;
		cocos2d::Label *countLabel;

		bool initSceneUI();
		bool initCoin();

		int randomCoinCount();
		void randomCoinLocal(cocos2d::Sprite *sprite);
		void operationCoin();
		void reloadCoin();
	};
}



#endif // __HELLOWORLD_SCENE_H__
