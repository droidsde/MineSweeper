//
//  SelectButtonSprite.cpp
//  MineSweeper
//
//  Created by 吉田　理貴 on 2015/10/15.
//
//

#include "SelectButtonSprite.h"

USING_NS_CC;

// コンストラクタ
SelectButtonSprite::SelectButtonSprite()
: _positionIndex(0, 0)
{
}

// インスタンス生成
SelectButtonSprite* SelectButtonSprite::create(PositionIndex positionIndex, ButtonType buttonType)
{
    SelectButtonSprite* pRet = new SelectButtonSprite();
    if (pRet && pRet->init(positionIndex, buttonType)) {
        pRet->autorelease();
    } else {
        delete pRet;
        pRet = nullptr;
    }
    
    return pRet;
}

// 初期化
bool SelectButtonSprite::init(PositionIndex positionIndex, ButtonType buttonType)
{
    if (!Sprite::initWithFile(getButtonImageFilePath(buttonType))) {
        return false;
    }
    
    _buttonType = buttonType;
    setPositionIndex(positionIndex);
    
    return true;
}

// ボタンの画像を変更
void SelectButtonSprite::changeButtonImageTexture()
{
    setTexture(getButtonImageFilePath(_buttonType));
}

// 選択中のボタン画像に変更
void SelectButtonSprite::changeSelectedButtonImageTexture()
{
    setTexture(getSelectedButtonImageFilePath(_buttonType));
}

// 位置インデックスを返す
SelectButtonSprite::PositionIndex SelectButtonSprite::getPositionIndex()
{
    return _positionIndex;
}

// 位置インデックスとタグを変更する
void SelectButtonSprite::setPositionIndex(PositionIndex positionIndex)
{
    // 位置インデックスを保持する
    _positionIndex = positionIndex;
    // 位置を変更する
    setPosition(getPointForPositionIndex(_positionIndex));
    // タグをセットする
    setTag(getGenerateTag(_positionIndex));
}

// グリッド画像の取得
std::string SelectButtonSprite::getButtonImageFilePath(ButtonType buttonType)
{
    switch (buttonType) {
        case ButtonType::Open:
            return "openButton.png";
        case ButtonType::PlantFlag:
            return "selectFlagButton.png";
        case ButtonType::RemoveFlag:
            return "removeFlagButton.png";
        default:
            return "selectButton.png";
    }
}

// 選択中のボタン画像取得
std::string SelectButtonSprite::getSelectedButtonImageFilePath(ButtonType buttonType)
{
    switch (buttonType) {
        case ButtonType::Open:
            return "openedButton.png";
        case ButtonType::PlantFlag:
            return "selectedFlagButton.png";
        case ButtonType::RemoveFlag:
            return "removedFlagButton.png";
        default:
            return "selectButton.png";
    }
}

// 位置インデックスからPointを取得
Point SelectButtonSprite::getPointForPositionIndex(PositionIndex positionIndex)
{
    return Point(SELECT_BUTTON_SIZE * (positionIndex.x - 2) * 1.5 + (WINSIZE.width / 2),
                 SELECT_BUTTON_SIZE * (positionIndex.y - 0.5) + WINSIZE.height / 5);
}

// 位置インデックスからタグを取得
int SelectButtonSprite::getGenerateTag(PositionIndex positionIndex)
{
    return SELECT_BUTTON_TAG + positionIndex.x * 10 + positionIndex.y;
}

