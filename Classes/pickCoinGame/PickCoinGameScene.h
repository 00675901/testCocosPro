#ifndef __PICKCOIN_SCENE_H__
#define __PICKCOIN_SCENE_H__

#include "cocos2d.h"
#include <time.h>

class PickCoinGame : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(PickCoinGame);
};

#endif // __HELLOWORLD_SCENE_H__
