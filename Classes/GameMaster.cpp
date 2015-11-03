//
//  GameMaster.cpp
//  MineSweeper
//
//  Created by 吉田　理貴 on 2015/09/21.
//
//

#include "GameMaster.h"
#include <random>

USING_NS_CC;

GameMaster* GameMaster::create(int bombNumber)
{
    GameMaster* pRet = new GameMaster();
    if (pRet && pRet->init(bombNumber)) {
        pRet->autorelease();
    } else {
        delete pRet;
        pRet = nullptr;
    }
    
    return pRet;
}

bool GameMaster::init(int bombNumber)
{
    createBoard(bombNumber);
    gameStatus = GameStatus::Open;
    return true;
}

GameMaster::GameStatus GameMaster::getGameStatus()
{
    return gameStatus;
}

void GameMaster::changeGameStatus(GameStatus status)
{
    gameStatus = status;
}

void GameMaster::createBoard(int bombNumber) {
    board.reserve(GRID_NUM_X);
    for (int i = 0; i < GRID_NUM_X; i++) board[i].reserve(GRID_NUM_Y);
    
    for (int i = 0; i < GRID_NUM_X; i++) {
        board.push_back( std::vector<int>() );
        for (int j = 0; j < GRID_NUM_Y; j++) {
            board[i].push_back(0);
        }
    }
}

void GameMaster::setBoardType(int x, int y, BoardType boardType)
{
    //board[x][y] = boardType;
}

int GameMaster::getBoardType(int x, int y)
{
    return 0;
}

GameMaster::BoardType GameMaster::getRandomBoardType() {
    switch (arc4random()%3) {
        case 0:
            return BoardType::White;
        case 1:
            return BoardType::Normal;
        case 2:
            return BoardType::Bomb;
        default:
            return BoardType::Normal;
    }
}

int GameMaster::getRandomNumber() {
    return arc4random()%10;
}
