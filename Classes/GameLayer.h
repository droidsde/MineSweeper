//
//  GameLayer.h
//  MineSweeper
//
//  Created by 吉田　理貴 on 2015/08/13.
//
//

#ifndef __MineSweeper__GameLayer__
#define __MineSweeper__GameLayer__

#include "cocos2d.h"

#define WINSIZE Director::getInstance()->getWinSize() // 画面サイズ取得用マクロ

class GameLayer : public cocos2d::Layer
{
protected:
    enum ZOrder {
        Z_Background,
    };
    
    enum Tab {
        T_Background,
    };
    
    void initBackground(); // 背景の初期化
    
public:
    GameLayer(); // コンストラクタ
    virtual bool init(); // 初期化
    CREATE_FUNC(GameLayer); // create関数生成
    static cocos2d::Scene* createScene(); // シーン生成
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif /* defined(__MineSweeper__GameLayer__) */