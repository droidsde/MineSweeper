//
//  GameLayer.h
//  MineSweeper
//
//  Created by 吉田　理貴 on 2015/08/13.
//
//

#ifndef __MineSweeper__GameLayer__
#define __MineSweeper__GameLayer__

#include "Common.h"
#include "GridSprite.h"
#include "SelectButtonSprite.h"
#include "GameMaster.h"

class GameLayer : public cocos2d::Layer
{
protected:
    enum ZOrder {
        Z_Background,
        Z_Grid,
        Z_SelectButton,
        Z_OpenButton,
        Z_FlagButton,
        Z_Particle,
    };
    
    enum Tab {
        T_Background,
        T_Grid,
        T_SelectButton,
        T_OpenButton,
        T_FlagButton,
        T_Particle,
    };
    
    void changeGridTexture(cocos2d::Touch* touch, GridSprite* grid); // Gridの画像を変更する
    
    ParticleSystemPool* _particlePool; // パーティクルプール
    
    GameMaster* _gameMaster; // ゲームマスター
    
    GridSprite* newGrid(GridSprite::GridType gridType, GridSprite::PositionIndex positionIndex); // 新規グリッド作成
    SelectButtonSprite* newSelectButton(SelectButtonSprite::ButtonType buttonType, SelectButtonSprite::PositionIndex positionIndex); // 選択ボタン作成
    GridSprite* getTouchGrid(cocos2d::Point touchPos, GridSprite::PositionIndex withoutPosIndex = GridSprite::PositionIndex()); // タッチしたグリッドを取得
    SelectButtonSprite* getTouchSelectButton(cocos2d::Point touchPos, SelectButtonSprite::PositionIndex withoutPosIndex = SelectButtonSprite::PositionIndex()); // タッチした選択ボタンを取得
    void initBackground(); // 背景の初期化
    void initGrids(int bombNumber); // グリッドの初期表示
    void initSelectButton(); // 選択ボタンの初期表示
    int checkBomb(int x, int y); // 爆弾のチェック
    
    // void showEffect(std::string soundEffect, cocos2d::Touch* touch, ParticleSystemPool* particlePool); // エフェクト表示
    void showEffect(cocos2d::Touch* touch, ParticleSystemPool* particlePool); // エフェクト表示
    
    GridSprite::PositionIndex getRandomGridPosition(); // ランダムにGridPositionを取得する
    
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