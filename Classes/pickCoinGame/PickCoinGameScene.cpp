#include "PickCoinGameScene.h"
#include "ClickSprite.h"

USING_NS_CC;

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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Texture2D * texture = nullptr;
	Image* image = image = new Image();

	if (nullptr != image&&image->initWithImageFile("HelloWorld.png")) {
		texture = new Texture2D();
		if (texture && texture->initWithImage(image)) {
			for (int i = 0; i < 30; ++i) {
				srand(i);
				int tempEnd = visibleSize.width - texture->getContentSize().width;
				int x = texture->getContentSize().width + rand() % tempEnd;
				tempEnd = visibleSize.height - texture->getContentSize().height;
				int y = texture->getContentSize().height + rand() % tempEnd;

				ClickSprite* testIcon = ClickSprite::create(texture);

				testIcon->setTag(i);
				testIcon->setPosition(Vec2(x, y));
				this->addChild(testIcon);
			}
		}
	}
}
