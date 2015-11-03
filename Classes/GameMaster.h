//
//  GameMaster.h
//  MineSweeper
//
//  Created by 吉田　理貴 on 2015/09/21.
//
//

#ifndef __MineSweeper__GameMaster__
#define __MineSweeper__GameMaster__

#include "Common.h"
#include <vector>

#define GRID_NUM_X 10
#define GRID_NUM_Y 10
#define SELECT_BUTTON_X 5
#define SELECT_BUTTON_Y 1
#define BOMB_NUM   40

class GameMaster : public cocos2d::Layer
{
public:
    enum class BoardType
    {
        White = 0,
        Normal = 1,
        Bomb = 2,
    };
    
    // ゲーム状態
    enum class GameStatus
    {
        Open,
        Flag,
    };
    
    static GameMaster* create(int bombNumber); // インスタンス生成
    virtual bool init(int bombNumber); // 初期化
    void createBoard(int bombNumber); // ゲームの盤面を作成する
    void setBoardType(int x, int y, BoardType boardType); // 盤面にボードタイプをセットする
    int getBoardType(int x, int y); // 盤面のボードタイプを取得する
    
    GameStatus getGameStatus(); // ゲーム状態の取得
    void changeGameStatus(GameStatus status); // ゲーム状態の変更
    
    GameStatus gameStatus; // ゲーム状態
    
    std::vector< std::vector<int> > board;
    
protected:
    BoardType getRandomBoardType();
    int getRandomNumber();
};

#endif /* defined(__MineSweeper__GameMaster__) */
