#ifndef __PICKCOIN_PLAYER_LAYER_H__
#define __PICKCOIN_PLAYER_LAYER_H__

#include "cocos2d.h"

namespace ccUniversal {
	class PlayerLayer : public cocos2d::Layer {
	public:
		~PlayerLayer();
		bool init();

		// implement the "static create()" method manually
		CREATE_FUNC(PlayerLayer);
	};
}

#endif // __PICKCOIN_PLAYER_LAYER_H__
