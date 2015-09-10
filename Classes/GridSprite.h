//
//  GridSprite.h
//  MineSweeper
//
//  Created by 吉田　理貴 on 2015/09/10.
//
//

#ifndef __LightsOut__GridSprite__
#define __LightsOut__GridSprite__

#include "cocos2d.h"

#define GRID_SIZE 64
#define WINSIZE Director::getInstance()->getWinSize() // 画面サイズ取得用マクロ

class GridSprite : public cocos2d::Sprite
{
public:
    enum class GridType
    {
        White,
        Normal,
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
    
    GridSprite(); // コンストラクタ
    static GridSprite* create(PositionIndex positionIndex, GridType gridType); // インスタンス生成
    virtual bool init(PositionIndex positionIndex, GridType gridType); // 初期化
    void changeTexture(GridType gridType); // 画像を変更
    
    CC_SYNTHESIZE_READONLY(GridType, _gridType, GridType); // グリッドの種類
    CC_PROPERTY(PositionIndex, _positionIndex, PositionIndex); // 位置インデックス
    
    std::string getGridImageFilePath(GridType gridType); // グリッド画像取得
    static cocos2d::Point getPositionForPositionIndex(PositionIndex positionIndex); // 位置インデックスからタグを取得
    static int getGenerateTag(PositionIndex positionIndex); // 位置インデックスからタグを取得
    
protected:
};

#endif /* defined(__LightsOut__GridSprite__) */