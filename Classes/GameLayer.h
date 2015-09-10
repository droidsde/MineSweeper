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
#include "GridSprite.h"

#define WINSIZE Director::getInstance()->getWinSize() // 画面サイズ取得用マクロ

#define GRID_NUM_X 10
#define GRID_NUM_Y 10

class GameLayer : public cocos2d::Layer
{
protected:
    enum ZOrder {
        Z_Background,
        Z_Grid,
    };
    
    enum Tab {
        T_Background,
        T_Grid,
    };
    
    void initBackground(); // 背景の初期化
    void initGrids(); // グリッドの初期表示
    
    GridSprite* newGrid(GridSprite::GridType gridType, GridSprite::PositionIndex positionIndex); // 新規グリッド作成
    
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