#include "PickCoinGameScene.h"

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
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    Texture2D * texture = nullptr;
    Image* image = image = new Image();
    if (nullptr != image&&image->initWithImageFile("Anchor.png")) {
        texture = new Texture2D();
        if (texture && texture->initWithImage(image)) {
            
            EventListenerTouchOneByOne *listener=EventListenerTouchOneByOne::create();
            listener->setSwallowTouches(true);
            listener->onTouchBegan = CC_CALLBACK_2(PickCoinGame::onTouchBegan, this);
            listener->onTouchMoved = CC_CALLBACK_2(PickCoinGame::onTouchMoved, this);
            listener->onTouchEnded = CC_CALLBACK_2(PickCoinGame::onTouchEnded, this);
            
            Sprite *s00=Sprite::createWithTexture(texture);
            s00->setAnchorPoint(Vec2(0,0));
            s00->setPosition(Vec2(0, 0));
            this->addChild(s00);
            
            Sprite *s01=Sprite::createWithTexture(texture);
            s01->setAnchorPoint(Vec2(0,0));
            s01->setPosition(Vec2(0, visibleSize.height-s01->getContentSize().height));
            this->addChild(s01);
            _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, s01);
            
            Sprite *s10=Sprite::createWithTexture(texture);
            s10->setAnchorPoint(Vec2(0,0));
            s10->setPosition(Vec2(visibleSize.width-s10->getContentSize().width,0));
            this->addChild(s10);
            
            Sprite *s11=Sprite::createWithTexture(texture);
            s11->setAnchorPoint(Vec2(0,0));
            s11->setPosition(Vec2(visibleSize.width-s11->getContentSize().width, visibleSize.height-s11->getContentSize().height));
            this->addChild(s11);
            texture->release();
            initCoin();
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool PickCoinGame::initCoin(){
    Texture2D * texture = nullptr;
    Image* image = image = new Image();
    if (nullptr != image&&image->initWithImageFile("testCoin.png")) {
        texture = new Texture2D();
        if (texture && texture->initWithImage(image)) {
            srand(time(NULL));
            Size textureSize=texture->getContentSize();
            for (int i = 0; i < 30; ++i) {
                ClickSprite* testIcon = ClickSprite::create(texture);
                testIcon->setTag(i);
                testIcon->setAnchorPoint(Vec2(0,0));
                randomCoinLocal(testIcon, textureSize);
                testIcon->setCallback(CC_CALLBACK_1(PickCoinGame::spriteCallback, this));
                this->addChild(testIcon);
                spriteCache.pushBack(testIcon);
            }
            texture->release();
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

void PickCoinGame::spriteCallback(Ref *sprite){
    auto target = static_cast<Sprite*>(sprite);
    log("sprite Tag:(%d)\n",target->getTag());
    target->removeFromParent();
}

void PickCoinGame::randomCoinLocal(cocos2d::Sprite *sprite,Size amendSize){
    int tempEnd = visibleSize.width - amendSize.width-200;
    int x = 100+rand() % tempEnd;
    tempEnd = visibleSize.height - amendSize.height;
    int y = rand() % tempEnd;
    sprite->setPosition(Vec2(x, y));
}

bool PickCoinGame::onTouchBegan(Touch* touch, Event* event){
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Point locationInNode = target->convertToNodeSpace(touch->getLocation());
    Size s = target->getContentSize();
    Rect rect = Rect(0, 0, s.width, s.height);
    if (rect.containsPoint(locationInNode)) {
        return true;
    }
    return false;
}
void PickCoinGame::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){}
void PickCoinGame::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
    if (!spriteCache.empty()) {
        for(auto e : spriteCache) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            e->removeFromParent();
            Size s = target->getContentSize();
            this->addChild(e);
            randomCoinLocal(e, s);
        }
    }
}
