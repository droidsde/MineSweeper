//
//  GridSprite.cpp
//  MineSweeper
//
//  Created by 吉田　理貴 on 2015/09/10.
//
//

#include "GridSprite.h"

USING_NS_CC;

// コンストラクタ
GridSprite::GridSprite()
: _positionIndex(0, 0)
, _flag(false)
{
}

// インスタンス生成
GridSprite* GridSprite::create(PositionIndex positionIndex, GridType gridType)
{
    GridSprite* pRet = new GridSprite();
    if (pRet && pRet->init(positionIndex, gridType)) {
        pRet->autorelease();
    } else {
        delete pRet;
        pRet = nullptr;
    }
    
    return pRet;
}

// 初期化
bool GridSprite::init(PositionIndex positionIndex, GridType gridType)
{
    if (!Sprite::initWithFile(getGridImageFilePath(gridType))) {
        return false;
    }
        
    _gridType = gridType;
    setPositionIndex(positionIndex);
    
    return true;
}

// 白いグリッドに変更
void GridSprite::changeWhiteGrid(int i) {
    setTexture(getGridImageFilePath(GridType::White));
    setGridType(GridType::White);
    showNumber(i);
}

// 画像を変更
void GridSprite::changeTexture(GridType gridType)
{
    _gridType = gridType;
    setTexture(getGridImageFilePath(_gridType));
}

// Gridにフラグを置く
void GridSprite::putFlag()
{
    if (getGridType() == GridType::Normal || getGridType() == GridType::Bomb) {
        if (!getFlag()) {
            setFlag(true);
            
            auto flag = Sprite::create("flag.png");
            if (flag) {
                flag->setPosition(Point(getContentSize() / 2));
                addChild(flag, Z_Flag, T_Flag);
            }
        }
    }
}

void GridSprite::removeFlag()
{
    if (getFlag()) {
        setFlag(false);
        removeChildByTag(T_Flag);
    }
}

// Gridに爆弾を置く
void GridSprite::putBomb()
{
    _gridType = GridType::Bomb;
    auto bomb = Sprite::create();
    bomb->setTexture("bomb.png");
    bomb->setPosition(Point(getContentSize() / 2));
    addChild(bomb);
    
    setTexture(getGridImageFilePath(_gridType));
}

void GridSprite::showNumber(int i)
{
    std::string numberString = StringUtils::format("%d", i);
    Color4B textColor = Color4B::BLACK;
    
    auto number = Label::createWithSystemFont(numberString, "Arial", 48);
    number->setPosition(Point(getContentSize() / 2));
    number->setTextColor(textColor);
    addChild(number);
}

// 位置インデックスを返す
GridSprite::PositionIndex GridSprite::getPositionIndex()
{
    return _positionIndex;
}

// 位置インデックスとタグを変更する
void GridSprite::setPositionIndex(PositionIndex positionIndex)
{
    // 位置インデックスを保持する
    _positionIndex = positionIndex;
    // 位置を変更する
    setPosition(getPointForPositionIndex(_positionIndex));
    // タグをセットする
    setTag(getGenerateTag(_positionIndex));
}

// グリッド画像の取得
std::string GridSprite::getGridImageFilePath(GridType gridType)
{
    switch (gridType) {
        case GridType::White:
            return "whiteButton.png";
        case GridType::Normal:
            return "button.png";
        case GridType::Bomb:
            return "button.png";
        default:
            return "button.png";
    }
}

// 位置インデックスからPointを取得
Point GridSprite::getPointForPositionIndex(PositionIndex positionIndex)
{
    return Point(GRID_SIZE * (positionIndex.x - 0.5),
                 GRID_SIZE * (positionIndex.y - 0.5) + WINSIZE.height * 2 / 5);
}

// 位置インデックスからタグを取得
int GridSprite::getGenerateTag(PositionIndex positionIndex)
{
    return GRID_TAG + positionIndex.x * 10 + positionIndex.y;
}