//
//  GridSprite.h
//  MineSweeper
//
//  Created by 吉田　理貴 on 2015/09/10.
//
//

#ifndef __LightsOut__GridSprite__
#define __LightsOut__GridSprite__

#include "Common.h"
#include "ParticleSystemPool.h"

#define GRID_SIZE 64

class GridSprite : public cocos2d::Sprite
{
public:
    enum class GridType
    {
        White,
        Normal,
        Bomb,
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
    void changeWhiteGrid(int i); // 白いグリッドに変更
    void changeTexture(GridType gridType); // 画像を変更
    void putFlag(); // Gridにフラグを置く
    void putBomb(); // Gridに爆弾を置く
    void showNumber(int i); // グリッドの数字を表示
        
    CC_SYNTHESIZE(GridType, _gridType, GridType); // グリッドの種類
    CC_SYNTHESIZE(bool, _flag, Flag);
    CC_PROPERTY(PositionIndex, _positionIndex, PositionIndex); // 位置インデックス
    
    std::string getGridImageFilePath(GridType gridType); // グリッド画像取得
    static cocos2d::Point getPointForPositionIndex(PositionIndex positionIndex); // 位置インデックスからポイントを取得
    static int getGenerateTag(PositionIndex positionIndex); // 位置インデックスからタグを取得
    
protected:
};

#endif /* defined(__LightsOut__GridSprite__) */