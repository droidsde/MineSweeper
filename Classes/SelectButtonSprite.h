//
//  SelectButtonSprite.h
//  MineSweeper
//
//  Created by 吉田　理貴 on 2015/10/15.
//
//

#ifndef __MineSweeper__SelectButtonSprite__
#define __MineSweeper__SelectButtonSprite__

#include "Common.h"

#define SELECT_BUTTON_SIZE 128

class SelectButtonSprite : public cocos2d::Sprite
{
public:
    enum class ButtonType
    {
        Open,
        PlantFlag,
        RemoveFlag,
    };
    
    // 位置インデックス
    struct PositionIndex {
        // コンストラクタ
        PositionIndex() {
            x = 0;
            y = 0;
        }
        
        // コンストラクタ
        PositionIndex(int _x, int _y) {
            x = _x;
            y = _y;
        }
        int x; // x方向のインデックス
        int y; // y方向のインデックス
    };
    
    SelectButtonSprite(); // コンストラクタ
    static SelectButtonSprite* create(PositionIndex positionIndex, ButtonType buttonType); // インスタンス生成
    virtual bool init(PositionIndex positionIndex, ButtonType buttonType); // 初期化
    void changeButtonImageTexture(); // ボタンの画像を変更
    void changeSelectedButtonImageTexture(); // 選択中のボタン画像に変更
    
    CC_SYNTHESIZE(ButtonType, _buttonType, ButtonType); // ボタンの種類
    CC_PROPERTY(PositionIndex, _positionIndex, PositionIndex); // 位置インデックス
    
    std::string getButtonImageFilePath(ButtonType buttonType); // ボタン画像取得
    std::string getSelectedButtonImageFilePath(ButtonType buttonType); // 選択中のボタン画像取得
    static cocos2d::Point getPointForPositionIndex(PositionIndex positionIndex); // 位置インデックスからポイントを取得
    static int getGenerateTag(PositionIndex positionIndex); // 位置インデックスからタグを取得
    
protected:
};

#endif /* defined(__MineSweeper__SelectButtonSprite__) */
