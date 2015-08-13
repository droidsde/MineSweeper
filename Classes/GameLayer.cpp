//
//  GameLayer.cpp
//  MineSweeper
//
//  Created by 吉田　理貴 on 2015/08/13.
//
//

#include "GameLayer.h"

USING_NS_CC;

// コンストラクタ
GameLayer::GameLayer()
{
}

// シーンの生成
Scene* GameLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLayer::create();
    scene->addChild(layer);
    
    return scene;
}

// 初期化
bool GameLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // シングルタップイベントの取得
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(_swallowsTouches);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    initBackground(); // 背景の初期化
    
    return true;
}

// 背景の初期化
void GameLayer::initBackground()
{
    auto background = Sprite::create("background.png");
    background->setAnchorPoint(Point::ZERO);
    background->setPosition(Point::ZERO);
    addChild(background, Z_Background, T_Background);
}

bool GameLayer::onTouchBegan(Touch* touch, Event* unused_event)
{
    return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event)
{
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event)
{
}

void GameLayer::onTouchCancelled(Touch* touch, Event* unused_event)
{
}