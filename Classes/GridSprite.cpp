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

// 画像を変更
void GridSprite::changeTexture(GridType gridType)
{
    _gridType = gridType;
    setTexture(getGridImageFilePath(_gridType));
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
    setPosition(getPositionForPositionIndex(_positionIndex));
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
    }
}

// 位置インデックスからPointを取得
Point GridSprite::getPositionForPositionIndex(PositionIndex positionIndex)
{
    return Point(GRID_SIZE * (positionIndex.x - 0.5),
                 GRID_SIZE * (positionIndex.y - 0.5) + WINSIZE.height / 4);
}

// 位置インデックスからタグを取得
int GridSprite::getGenerateTag(PositionIndex positionIndex)
{
    return positionIndex.x * 10 + positionIndex.y;
}