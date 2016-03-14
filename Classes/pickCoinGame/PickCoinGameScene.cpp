#include "PickCoinGameScene.h"

USING_NS_CC;

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
	countLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 25);
	countLabel->setAnchorPoint(Vec2(0.5, 1));
	countLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
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
			coinSprite->setAnchorPoint(Vec2::ZERO);
			coinSprite->setCallback(CC_CALLBACK_1(PickCoinGame::spriteCallback, this));
			randomCoinLocal(coinSprite);
			spriteCache.pushBack(coinSprite);
		}
		this->addChild(mainLayer);
		reloadCoin();
		return true;
	} else {
		false;
	}
}

void PickCoinGame::reloadCoin() {
	mainLayer->removeAllChildren();
	currCoinCount = randomCoinCount();
	int i = 0;
	for (auto e : spriteCache) {
		mainLayer->addChild(e);
		randomCoinLocal(e);
		i++;
		if (i >= currCoinCount) {
			break;
		}
	}
	countLabel->setString(StringUtils::toString(currCoinCount));
}

void PickCoinGame::randomCoinLocal(cocos2d::Sprite *sprite) {
	Size sSize = sprite->getContentSize();
	int tempStart = coinLocalRang.origin.x;
	int tempEnd = tempStart + coinLocalRang.size.width - sSize.width;
	int x = rand() % (tempEnd - tempStart + 1) + tempStart;

	tempStart = coinLocalRang.origin.y;
	tempEnd = tempStart + coinLocalRang.size.height - sSize.height;
	int y = rand() % (tempEnd - tempStart + 1) + tempStart;
	sprite->setPosition(Vec2(x, y));
}

int PickCoinGame::randomCoinCount() {
	srand(time(NULL));
	int x = rand() % (maxCoinCount - 23 + 1) + 23;
	log("maxCoinCount:%d result:%d\n", maxCoinCount, x);
	return x;
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
		log("44444444444444444\n");
		break;
	default:
		break;
	}

}

void PickCoinGame::spriteCallback(Ref *sprite) {
	Sprite* target = static_cast<Sprite*>(sprite);
	log("sprite Tag:(%d)\n", target->getTag());
	target->removeFromParent();
	currCoinCount--;
	countLabel->setString(StringUtils::toString(currCoinCount));
}
