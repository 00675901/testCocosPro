#ifndef __PICKCOIN_PLAYER_LAYER_H__
#define __PICKCOIN_PLAYER_LAYER_H__

#include "PCGPlayerSprite.h"
#include "cocos2d.h"

class PCGPlayerLayer : public cocos2d::Layer {
  public:
    PCGPlayerLayer();
    ~PCGPlayerLayer();
    bool init();
    bool initUI();
    // implement the "static create()" method manually
    CREATE_FUNC(PCGPlayerLayer);

    cocos2d::Size playerSize();

    void changePlayer();
    bool canBeOperation(int count);
    void reloadPlayer();

    PCGPlayerSprite* currPlayer;
    cocos2d::Label* currRepeatLabel;

  private:
    cocos2d::Size visibleSize;
    cocos2d::Vector<PCGPlayerSprite*> playerList;
    
    PCGPlayerSprite* player1;
    cocos2d::Label* repeatLabel1;

    PCGPlayerSprite* player2;
    cocos2d::Label* repeatLabel2;
};

#endif // __PICKCOIN_PLAYER_LAYER_H__
