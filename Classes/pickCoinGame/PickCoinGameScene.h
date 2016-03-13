#ifndef __PICKCOIN_SCENE_H__
#define __PICKCOIN_SCENE_H__

#include "cocos2d.h"
#include <time.h>
#include "ClickSprite.h"

class PickCoinGame : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	bool init();
    bool initCoin();
    
    void randomCoinLocal(cocos2d::Sprite *sprite,cocos2d::Size amendSize);
	// implement the "static create()" method manually
	CREATE_FUNC(PickCoinGame);
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void spriteCallback(Ref *sprite);
private:
    cocos2d::Vector<cocos2d::Sprite*> spriteCache;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
};

#endif // __HELLOWORLD_SCENE_H__
