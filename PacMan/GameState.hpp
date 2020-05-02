//
//  GameState.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 02/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef GameState_hpp
#define GameState_hpp

#include "AllInterfaces.h"
namespace pacman {namespace impl{
    class GameState{
        int                           mScore;
        IBluePrintPtr                 mBluePrint;
        int                           mGhostCount = 0;
        int                           mPlayerCount = 0;
        VecVecInt                     mBoard;
    public:
        GameState(IBluePrintPtr ptr):mBluePrint(ptr){
            create();
        }
        
        bool canMove(Coordinates c){
            return mBoard[c.col][c.row] != mapElements::Wall;
        }
        
        void move(Coordinates from, Coordinates to){
            if((mBoard[from.row][from.col] == mapElements::PlayerPos ||
                mBoard[from.row][from.col] == mapElements::GhostPos) &&
               mBoard[to.row][to.col] == mapElements::Empty){
                std::swap(mBoard[from.row][from.col],  mBoard[to.row][to.col]);
            }
        }
        
        bool isGhost(Coordinates c){
            return mBoard[c.col][c.row] == mapElements::GhostPos;
        }
        bool isPlayer(Coordinates c){
            return mBoard[c.col][c.row] == mapElements::PlayerPos;
        }
        
        size_t getRows(){
            return mBluePrint->getRow();
        }
        
        void addToBoard(Coordinates c, int num){
            mBoard[c.row][c.col] += num;
        }
        
        int getBoardNum(Coordinates c){
            return mBoard[c.row][c.col];
        }
        
        size_t getCols(){
            return mBluePrint->getCol();
        }
        
        void addScore(int s){
            mScore += s;
        }
    private:
        void create(){
            mBoard = VecVecInt(mBluePrint->getRow(),
                               VectorInt(mBluePrint->getCol(), mapElements::Empty));
            for(size_t i = 0; i < mBluePrint->getRow(); i++){
                for(size_t j = 0; j < mBluePrint->getCol(); j++){
                    if (mBluePrint->isWall(Coordinates(i, j))) {
                        mBoard[i][j] = (size_t)mapElements::Wall;
                    }
                    else if (mBluePrint->isEmpty(Coordinates(i, j))) {
                        mBoard[i][j] = (size_t)mapElements::Empty;
                    }
                    else if (mBluePrint->isGhost(Coordinates(i, j))) {
                        mBoard[i][j] = (size_t)mapElements::Wall;
                    }
                    else {
                        mBoard[i][j] = (size_t)mapElements::PlayerPos;
                    }
                }
            }
        }
    };
}}


#endif /* GameState_hpp */
