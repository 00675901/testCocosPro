#include "ClickSprite.h"

USING_NS_CC;

ClickSprite::ClickSprite() {}
ClickSprite::~ClickSprite() {
    _eventDispatcher->removeEventListener(listener);
    log("Click_Sprite release\n");
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

void ClickSprite::setCallback(const clickSpriteCallback& callback){
    _callback = callback;
}

bool ClickSprite::initWithTexture(cocos2d::Texture2D *texture) {
    if (!Sprite::initWithTexture(texture)) {
        return false;
    }
    
    listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        if (rect.containsPoint(locationInNode)) {
            log("sprite Tag(%d)  x = %f, y = %f", target->getTag(), locationInNode.x, locationInNode.y);
            if( _callback ){
                _callback(this);
            }
            return true;
        }
        return false;
    };
    listener->onTouchMoved = [](Touch* touch, Event* event) {};
    
    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        //        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        //        target->removeFromParent();
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}