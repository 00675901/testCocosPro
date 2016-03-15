#include "PickCoinGameScene.h"

USING_NS_CC;
using namespace ccPickCoinGame;

PickCoinGame::~PickCoinGame() {
	opeSpriteCache.clear();
	spriteCache.clear();
	log("Pick_Coin_Game release\n");
}

Scene *PickCoinGame::createScene() {
	auto scene = Scene::create();
	auto layer = PickCoinGame::create();
	scene->addChild(layer);
	return scene;
}

bool PickCoinGame::init() {
	if (!Layer::init()) {
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	initSceneUI();
	initCoin();

	maxCoinCount = 30;
	currCoinCount = randomCoinCount();
	Texture2D * texture = Director::getInstance()->getTextureCache()->addImage("Anchor.png");
	if (texture) {
		EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(PickCoinGame::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(PickCoinGame::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(PickCoinGame::onTouchEnded, this);

		Sprite *s00 = Sprite::createWithTexture(texture);
		s00->setAnchorPoint(Vec2(0, 0));
		s00->setPosition(Vec2(0, 0));
		s00->setTag(1);
		this->addChild(s00);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, s00);

		Sprite *s01 = Sprite::createWithTexture(texture);
		s01->setAnchorPoint(Vec2(0, 0));
		s01->setPosition(Vec2(0, visibleSize.height - s01->getContentSize().height));
		s01->setTag(2);
		this->addChild(s01);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), s01);

		Sprite *s11 = Sprite::createWithTexture(texture);
		s11->setAnchorPoint(Vec2(0, 0));
		s11->setPosition(Vec2(visibleSize.width - s11->getContentSize().width, visibleSize.height - s11->getContentSize().height));
		s11->setTag(3);
		this->addChild(s11);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), s11);

		Sprite *s10 = Sprite::createWithTexture(texture);
		s10->setAnchorPoint(Vec2(0, 0));
		s10->setPosition(Vec2(visibleSize.width - s10->getContentSize().width, 0));
		s10->setTag(4);
		this->addChild(s10);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), s10);

		return true;
	} else {
		return false;
	}
}

bool PickCoinGame::initSceneUI() {
	Texture2D *atlastexture = Director::getInstance()->getTextureCache()->addImage("fonts/atlas_fps.png");
	countLabel = Label::createWithCharMap(atlastexture, 100, 100, '0');
	countLabel->setString("0");
	countLabel->setAnchorPoint(Vec2::ZERO);
	Size sSize = countLabel->getContentSize();
	countLabel->setPosition(Vec2(visibleSize.width / 2 - sSize.width / 2, visibleSize.height - sSize.height));
	this->addChild(countLabel);
	return true;
}

bool PickCoinGame::initCoin() {
	srand(time(NULL));
	if (spriteCache.size() <= 0) {
		Size sSize1 = Director::getInstance()->getTextureCache()->addImage("Anchor.png")->getContentSize();
		Size sSize2 = Director::getInstance()->getTextureCache()->addImage("testCoin.png")->getContentSize();
		coinLocalRang = Rect(sSize1.width, 0, visibleSize.width - sSize1.width - sSize2.width, visibleSize.height - countLabel->getContentSize().height);
		mainLayer = Layer::create();
		for (int i = 0; i < maxCoinCount; ++i) {
			CoinSprite *coinSprite = CoinSprite::create();
			if (coinSprite == nullptr) {
				return false;
			}
			coinSprite->setTag(i);
			coinSprite->setCallback(CC_CALLBACK_2(PickCoinGame::spriteCallback, this));
			randomCoinLocal(coinSprite);
			spriteCache.pushBack(coinSprite);
		}
		this->addChild(mainLayer);
		reloadCoin();
		return true;
	} else {
		return false;
	}
}

void PickCoinGame::reloadCoin() {
	mainLayer->removeAllChildren();
	currCoinCount = randomCoinCount();
	int i = 0;
	for (auto e : spriteCache) {
		e->setScale(1.0f);
		mainLayer->addChild(e);
		randomCoinLocal(e);
		i++;
		if (i >= currCoinCount) {
			break;
		}
	}
	opeSpriteCache.clear();
	countLabel->setString(StringUtils::toString(currCoinCount));
}

void PickCoinGame::randomCoinLocal(cocos2d::Sprite *sprite) {
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	Size sSize = sprite->getContentSize();
	int tempStart = coinLocalRang.origin.x + sSize.width / 2;
	int tempEnd = coinLocalRang.origin.x + coinLocalRang.size.width - sSize.width / 2;
	int x = rand() % (tempEnd - tempStart + 1) + tempStart;

	tempStart = coinLocalRang.origin.y + sSize.height / 2;
	tempEnd = coinLocalRang.origin.y + coinLocalRang.size.height - sSize.height / 2;
	int y = rand() % (tempEnd - tempStart + 1) + tempStart;
	sprite->setPosition(Vec2(x, y));
}

int PickCoinGame::randomCoinCount() {
	srand(time(NULL));
	int x = rand() % (maxCoinCount - 23 + 1) + 23;
	return x;
}

void PickCoinGame::operationCoin() {
	for (auto e : opeSpriteCache) {
		e.second->setScale(1.0f);
		e.second->removeFromParent();
		currCoinCount--;
	}
	opeSpriteCache.clear();
	countLabel->setString(StringUtils::toString(currCoinCount));
}

bool PickCoinGame::onTouchBegan(Touch* touch, Event* event) {
	Sprite* target = static_cast<Sprite*>(event->getCurrentTarget());
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode)) {
		return true;
	}
	return false;
}
void PickCoinGame::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {}
void PickCoinGame::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	Sprite* target = static_cast<Sprite*>(event->getCurrentTarget());
	switch (target->getTag()) {
	case(1) :
		reloadCoin();
		break;
	case(2) :
		log("222222222222:%d\n", randomCoinCount());
		break;
	case(3) :
		log("33333333333333\n");
		break;
	case(4) :
		operationCoin();
		if (currCoinCount<=0) {
			reloadCoin();
		}
		break;
	}
}

void PickCoinGame::spriteCallback(cocos2d::Sprite* sprite, int actionTag) {
	int tag = sprite->getTag();
	if (1.0f != sprite->getScale()) {
		sprite->setScale(1.0f);
		opeSpriteCache.erase(tag);
		log("sprite Tag:(%d) Cancel , sprite count:%d\n", tag, opeSpriteCache.size());
	} else {
		if (opeSpriteCache.size() < pickCount) {
			sprite->setScale(1.5f);
			opeSpriteCache.insert(tag, sprite);
			log("sprite Tag:(%d) Selected , sprite count:%d\n", tag, opeSpriteCache.size());
		}
	}
}
