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

void PickCoinGame::setAI(bool isai) {
	this->isAI = isai;
}

bool PickCoinGame::init() {
	if (!Layer::init()) {
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	initResource();
	initSceneUI();
	initCoin();

	maxCoinCount = 30;
	currCoinCount = randomCoinCount();
	Texture2D * texture = Director::getInstance()->getTextureCache()->getTextureForKey("Anchor.png");
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

		//Sprite *s01 = Sprite::createWithTexture(texture);
		//s01->setAnchorPoint(Vec2(0, 0));
		//s01->setPosition(Vec2(0, visibleSize.height - s01->getContentSize().height));
		//s01->setTag(2);
		//this->addChild(s01);
		//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), s01);

		//Sprite *s11 = Sprite::createWithTexture(texture);
		//s11->setAnchorPoint(Vec2(0, 0));
		//s11->setPosition(Vec2(visibleSize.width - s11->getContentSize().width, visibleSize.height - s11->getContentSize().height));
		//s11->setTag(3);
		//this->addChild(s11);
		//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), s11);

		Sprite *s10 = Sprite::createWithTexture(texture);
		s10->setAnchorPoint(Vec2(0, 0));
		s10->setPosition(Vec2(visibleSize.width - s10->getContentSize().width, 0));
		s10->setTag(2);
		this->addChild(s10);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), s10);

		return true;
	} else {
		return false;
	}
}

bool PickCoinGame::initResource() {
	TextureCache* tc = Director::getInstance()->getTextureCache();
	tc->addImage("fonts/atlas_fps.png");
	tc->addImage("Anchor.png");
	tc->addImage("testCoin.png");
	tc->addImage("HelloWorld.png");

	return true;
}

bool PickCoinGame::initSceneUI() {
	Texture2D *atlastexture = Director::getInstance()->getTextureCache()->getTextureForKey("fonts/atlas_fps.png");
	countLabel = Label::createWithCharMap(atlastexture, 100, 100, '0');
	countLabel->setString("0");
	countLabel->setAnchorPoint(Vec2::ZERO);
	Size sSize = countLabel->getContentSize();
	countLabel->setPosition(Vec2(visibleSize.width / 2 - sSize.width / 2, visibleSize.height - sSize.height));
	this->addChild(countLabel);

	playerLayer = PCGPlayerLayer::create();
	this->addChild(playerLayer);

	return true;
}

bool PickCoinGame::initCoin() {
	srand(time(NULL));
	if (spriteCache.size() <= 0) {
		Size sSize1 = Director::getInstance()->getTextureCache()->getTextureForKey("Anchor.png")->getContentSize();
		Size sSize2 = Director::getInstance()->getTextureCache()->getTextureForKey("testCoin.png")->getContentSize();
		coinLocalRang = Rect(sSize1.width, 0, visibleSize.width - sSize1.width - sSize2.width, visibleSize.height - playerLayer->playerSize().height);
		mainLayer = Layer::create();
		for (int i = 0; i < maxCoinCount; ++i) {
			PCGCoinSprite *coinSprite = PCGCoinSprite::create();
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
	int tCount = opeSpriteCache.size();
	if (tCount > 0 && playerLayer->canBeOperation(tCount)) {
		for (auto e : opeSpriteCache) {
			e.second->setScale(1.0f);
			e.second->removeFromParent();
			currCoinCount--;
		}
		opeSpriteCache.clear();
		countLabel->setString(StringUtils::toString(currCoinCount));
		playerLayer->changePlayer();
	}
}

void PickCoinGame::operationCoinByAI() {
	srand(time(NULL));
	int x = rand() % 3 + 1;
	Vector<Node*> coins = mainLayer->getChildren();

	log("testtest:%d\n", coins.size());
	PCGPlayerSprite* pSprite = static_cast<PCGPlayerSprite*>(coins.getRandomObject());
	log("testtest222:%d,%d\n", pSprite->getTag(), coins.size());

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
		playerLayer->reloadPlayer();
		reloadCoin();
		break;
	case(2) :
		//operationCoin();
		//if (currCoinCount <= 0) {
		//	playerLayer->reloadPlayer();
		//	reloadCoin();
		//}
		operationCoinByAI();
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
