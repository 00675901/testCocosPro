#include "PCGPlayerLayer.h"

USING_NS_CC;

PCGPlayerLayer::PCGPlayerLayer() {
	log("PCGPlayerLayer new\n");
}

PCGPlayerLayer::~PCGPlayerLayer() {
	log("PCGPlayerLayer release\n");
}

bool PCGPlayerLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	Texture2D *playertexture = Director::getInstance()->getTextureCache()->getTextureForKey("HelloWorld.png");

	player1 = PCGPlayerSprite::create("PLAYER1", playertexture);
	player1->setAnchorPoint(Vec2(0, 1));
	player1->setPosition(0, visibleSize.height);
	this->addChild(player1);

	player2 = PCGPlayerSprite::create("PLAYER2", playertexture);
	player2->setAnchorPoint(Vec2(1, 1));
	player2->setPosition(visibleSize.width, visibleSize.height);
	this->addChild(player2);

	initUI();
	changePlayer();

	return true;
}

bool PCGPlayerLayer::initUI() {
	Size pSize = player1->getContentSize();
	Texture2D *atlastexture = Director::getInstance()->getTextureCache()->getTextureForKey("fonts/atlas_fps.png");
	repeatLabel1 = Label::createWithCharMap(atlastexture, 100, 100, '0');
	repeatLabel1->setString("0");
	repeatLabel1->setAnchorPoint(Vec2::ZERO);
	repeatLabel1->setPosition(pSize.width, player1->getPositionY() - (pSize.height / 2) - (repeatLabel1->getContentSize().height / 2));
	this->addChild(repeatLabel1);

	repeatLabel2 = Label::createWithCharMap(atlastexture, 100, 100, '0');
	repeatLabel2->setString("0");
	repeatLabel2->setAnchorPoint(Vec2::ZERO);
	repeatLabel2->setPosition(player2->getPositionX() - pSize.width - repeatLabel2->getContentSize().width, player2->getPositionY() - (pSize.height / 2) - (repeatLabel2->getContentSize().height / 2));
	this->addChild(repeatLabel2);

	return true;
}

Size PCGPlayerLayer::playerSize() {
	return player1->getContentSize();
}

void PCGPlayerLayer::changePlayer() {
	if (currPlayer != nullptr) {
		currPlayer->setScale(1.0f);
	}
	if (currPlayer != player1) {
		currPlayer = player1;
		currRepeatLabel = repeatLabel1;
	} else {
		currPlayer = player2;
		currRepeatLabel = repeatLabel2;
	}
	currPlayer->setScale(1.2f);
}

bool PCGPlayerLayer::canBeOperation(int count) {
	if (currPlayer->preNum == count) {
		currPlayer->repeatCount += 1;
	} else {
		currPlayer->repeatCount = 0;
		currPlayer->preNum = count;
	}
	if (currPlayer->repeatCount < 3) {
		currRepeatLabel->setString(StringUtils::toString(currPlayer->repeatCount));
		return true;
	} else {
		return false;
	}
}

void PCGPlayerLayer::reloadPlayer() {
	player1->preNum = 0;
	player1->repeatCount = 0;
	player1->setScale(1.0f);
	repeatLabel1->setString("0");

	player2->preNum = 0;
	player2->repeatCount = 0;
	player2->setScale(1.0f);
	repeatLabel2->setString("0");

	changePlayer();
}