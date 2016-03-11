#include "ClickSprite.h"

USING_NS_CC;

ClickSprite::ClickSprite() {}
ClickSprite::~ClickSprite() {
	_eventDispatcher->removeAllEventListeners();
}
ClickSprite* ClickSprite::create(cocos2d::Texture2D *texture) {

	ClickSprite* pSprite = new ClickSprite();
	if (pSprite->initWithTexture(texture)) {
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;

	return nullptr;
}
bool ClickSprite::initWithTexture(cocos2d::Texture2D *texture) {
	if (!Sprite::initWithTexture(texture)) {
		return false;
	}

	auto listener1 = EventListenerTouchOneByOne::create();
	// 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode)) {
			log("sprite Tag(%d)  x = %f, y = %f", target->getTag(), locationInNode.x, locationInNode.y);
			target->setOpacity(180);
			target->setVisible(false);
			return true;
		}
		return false;
	};

	listener1->onTouchMoved = [](Touch* touch, Event* event) {};

	listener1->onTouchEnded = [=](Touch* touch, Event* event) {};

	// 添加监听器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	return true;
}