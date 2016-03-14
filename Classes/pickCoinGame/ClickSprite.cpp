#include "ClickSprite.h"

USING_NS_CC;

ClickSprite::ClickSprite() {
	log("%s new\n", CLICK_SPRITE_TAG);
}
ClickSprite::~ClickSprite() {
	_eventDispatcher->removeEventListener(listener);
	log("%s release\n", CLICK_SPRITE_TAG);
}
ClickSprite* ClickSprite::create(cocos2d::Texture2D *texture) {
	ClickSprite* pSprite = new ClickSprite();
	if (pSprite->initWithTexture(texture)) {
		pSprite->autorelease();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return nullptr;
}

void ClickSprite::setCallback(const clickSpriteCallback& callback) {
	_callback = callback;
}

bool ClickSprite::initWithTexture(cocos2d::Texture2D *texture) {
	if (!Sprite::initWithTexture(texture)) {
		return false;
	}

	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ClickSprite::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ClickSprite::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ClickSprite::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool ClickSprite::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode)) {
		log("%s onTouchBegan", CLICK_SPRITE_TAG);
		log("%s Tag(%d)  x = %f, y = %f", CLICK_SPRITE_TAG, target->getTag(), locationInNode.x, locationInNode.y);
		return true;
	}
	return false;
}
void ClickSprite::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	//log("%s onTouchMoved", CLICK_SPRITE_TAG);
}
void ClickSprite::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	log("%s onTouchEnded", CLICK_SPRITE_TAG);
}