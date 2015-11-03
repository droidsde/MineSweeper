//
//  GameLayer.cpp
//  MineSweeper
//
//  Created by 吉田　理貴 on 2015/08/13.
//
//

#include "GameLayer.h"
#include <random>

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
    
    _particlePool = ParticleSystemPool::create("plist/explosion.plist", 200);
    _particlePool->retain();
    
    _gameMaster = GameMaster::create(20);
    
    initBackground(); // 背景の初期化
    initGrids(BOMB_NUM); // グリッドの初期化
    initSelectButton(); // 選択ボタンの初期化
    
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

// グリッドの初期表示
void GameLayer::initGrids(int bombNumber)
{
    for (int i = 0; i < BOMB_NUM; i++) {
        newGrid(GridSprite::GridType::Bomb, getRandomGridPosition());
    }
    
    for (int x = 1; x <= GRID_NUM_X; x++) {
        for (int y = 1; y <= GRID_NUM_Y; y++) {
            int tag = GridSprite::getGenerateTag(GridSprite::PositionIndex(x, y));
            auto grid = (GridSprite*)(getChildByTag(tag));
            
            if (!grid) {
                newGrid(GridSprite::GridType::Normal, GridSprite::PositionIndex(x, y));
            }
        }
    }
    
}

void GameLayer::initSelectButton()
{
    
    newSelectButton(SelectButtonSprite::ButtonType::Open, SelectButtonSprite::PositionIndex(1,1));
    newSelectButton(SelectButtonSprite::ButtonType::Flag, SelectButtonSprite::PositionIndex(2,1));
    newSelectButton(SelectButtonSprite::ButtonType::Open, SelectButtonSprite::PositionIndex(3,1));
    newSelectButton(SelectButtonSprite::ButtonType::Open, SelectButtonSprite::PositionIndex(4,1));
    newSelectButton(SelectButtonSprite::ButtonType::Open, SelectButtonSprite::PositionIndex(5,1));
}

// 新規グリッドの作成
GridSprite* GameLayer::newGrid(GridSprite::GridType gridType, GridSprite::PositionIndex positionIndex)
{
    auto grid = GridSprite::create(positionIndex, gridType);
    grid->setPositionIndex(positionIndex);
    
    addChild(grid, ZOrder::Z_Grid);
    
    return grid;
}

// 選択ボタン作成
SelectButtonSprite* GameLayer::newSelectButton(SelectButtonSprite::ButtonType buttonType, SelectButtonSprite::PositionIndex positionIndex)
{
    auto button = SelectButtonSprite::create(positionIndex, buttonType);
    button->setPositionIndex(positionIndex);
    
    addChild(button, ZOrder::Z_SelectButton);
    
    return button;
}

GridSprite::PositionIndex GameLayer::getRandomGridPosition() {
    return GridSprite::PositionIndex(arc4random()%10 + 1, arc4random()%10 + 1);
}

void GameLayer::changeGridTexture(Touch* touch, GridSprite* grid)
{
    if (grid) {
        switch (grid->getGridType()) {
            case GridSprite::GridType::Normal:
                if (!grid->getFlag()) {
                    grid->changeWhiteGrid(checkBomb(grid->getPositionIndex().x, grid->getPositionIndex().y));
                }
                break;
            case GridSprite::GridType::Bomb:
                if (!grid->getFlag()) {
                    showEffect(touch, _particlePool);
                }
                break;
            case GridSprite::GridType::White:
                break;
        }
    }
}

//void GameLayer::showEffect(std::string soundEffect, Touch* touch, ParticleSystemPool* particlePool)
void GameLayer::showEffect(Touch* touch, ParticleSystemPool* particlePool)
{
    //SimpleAudioEngine::getInstance()->playEffect(soundEffect.c_str());
    auto particle = particlePool->pop();
    particle->setPosition(touch->getLocation());
    this->addChild(particle, Z_Particle, T_Particle);
}

// タップした位置のチェック
GridSprite* GameLayer::getTouchGrid(Point touchPos, GridSprite::PositionIndex withoutPosIndex)
{
    for (int x = 1; x <= GRID_NUM_X; x++) {
        for (int y = 1; y <= GRID_NUM_Y; y++) {
            if (x == withoutPosIndex.x && y == withoutPosIndex.y) {
                // 指定位置のグリッドの場合は、以下の処理を行わない
                continue;
            }
            
            // タップ位置にあるグリッドかどうかを判断する
            int tag = GridSprite::getGenerateTag(GridSprite::PositionIndex(x, y));
            
            auto grid = (GridSprite*)(getChildByTag(tag));
            if (grid) {
                // 2点間の距離を求める
                float distance = grid->getPosition().getDistance(touchPos);
                
                if (distance <= GRID_SIZE / 2) {
                    return grid;
                }
            }
        }
    }
    return nullptr;
}

SelectButtonSprite* GameLayer::getTouchSelectButton(Point touchPos, SelectButtonSprite::PositionIndex withoutPosIndex)
{
    for (int x = 1; x <= SELECT_BUTTON_X; x++) {
        for (int y = 1; y <= SELECT_BUTTON_Y; y++) {
            if (x == withoutPosIndex.x && y == withoutPosIndex.y) {
                // 指定位置のボタンの場合は、以下の処理を行わない
                continue;
            }
            
            int tag = SelectButtonSprite::getGenerateTag(SelectButtonSprite::PositionIndex(x, y));
            
            auto button = (SelectButtonSprite*)(getChildByTag(tag));
            if (button) {
                // 2点間の距離を求める
                float distance = button->getPosition().getDistance(touchPos);
                
                if (distance <= SELECT_BUTTON_SIZE / 2) {
                    return button;
                }
            }
            
        }
    }
    
    return nullptr;
}

bool GameLayer::onTouchBegan(Touch* touch, Event* unused_event)
{
    GridSprite* touchGrid = getTouchGrid(touch->getLocation());
    SelectButtonSprite* touchSelectButton = getTouchSelectButton(touch->getLocation());
    
    if (touchGrid) {
        switch (_gameMaster->getGameStatus()) {
            case GameMaster::GameStatus::Open:
                changeGridTexture(touch, touchGrid);
                break;
            case GameMaster::GameStatus::Flag:
                if (touchGrid) {
                    touchGrid->putFlag();
                }
                break;
        }
    } else if (touchSelectButton) {
        switch (touchSelectButton->getButtonType()) {
            case SelectButtonSprite::ButtonType::Open:
                _gameMaster->changeGameStatus(GameMaster::GameStatus::Open);
                break;
            case SelectButtonSprite::ButtonType::Flag:
                _gameMaster->changeGameStatus(GameMaster::GameStatus::Flag);
                break;
        }
    }
    
    return false;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event)
{
    GridSprite* touchGrid = getTouchGrid(touch->getLocation());
    if (_gameMaster->getGameStatus() == GameMaster::GameStatus::Open) {
        changeGridTexture(touch, touchGrid);
    }
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event)
{
}

void GameLayer::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchCancelled(touch, unused_event);
}

int GameLayer::checkBomb(int x, int y) {
    int sumBomb = 0;
    
    int dir_x[] = {1, -1, 0, 0, 1, 1, -1, -1};
    int dir_y[] = {0, 0, 1, -1, 1, -1, 1, -1};
    
    for (int i = 0; i < 8; i++) {
        if (x + dir_x[i] != 0 && x + dir_x[i] != 11 &&
            y + dir_y[i] != 0 && y + dir_y[i] != 11) {
            int tag = GridSprite::getGenerateTag(GridSprite::PositionIndex(x + dir_x[i], y + dir_y[i]));
            GridSprite* grid = (GridSprite*)(getChildByTag(tag));
            if (grid && grid->getGridType() == GridSprite::GridType::Bomb) sumBomb++;
        }
    }
    
    return sumBomb;
}
