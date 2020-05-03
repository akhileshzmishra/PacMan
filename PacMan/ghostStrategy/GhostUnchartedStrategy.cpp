//
//  GhostUnchartedStrategy.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 02/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "GhostUnchartedStrategy.hpp"
using namespace pacman;
using namespace pacman::impl;

static const int InvalidIndex = 10;

static const VecVecInt DeltaPos = {
    {-1, 0},
    {0, -1},
    {1, 0},
    {0, 1}
};

static const Directions DirVec[] = {
    Directions::UpDir,
    Directions::LeftDir,
    Directions::DownDir,
    Directions::RightDir
};

static const size_t MinInitialValue = std::numeric_limits<int>::max();

GhostUnchartedStrategy::GhostUnchartedStrategy(const GameState& st):
mState(st){
    
}
void GhostUnchartedStrategy::setBluePrint(IBluePrintPtr ptr){
    mPrint = ptr;
}

DirSuggestion GhostUnchartedStrategy::suggestNextMove(const Coordinates& coordinates, const Directions curDir){
    DirSuggestion suggestion(InvalidDir, coordinates);
    if(!mState.isGhost(coordinates)){
        return suggestion;
    }
    size_t deltaPos = InvalidIndex;
    int minVal = std::numeric_limits<int>::max();
    size_t i = (size_t)curDir;
    int count = 0;
    while(count < 4){
        AutoIncrementer autoIncrementer([&i, &count]{
            i = (i + 1)%4;
            count++;
        });
        Coordinates nxt;
        nxt.row = DeltaPos[i][0] + coordinates.row;
        nxt.col = DeltaPos[i][1] + coordinates.col;
        if(nxt.row < mState.getRows() && nxt.col < mState.getCols()){
            if(!mState.canMove(nxt)){
                continue;
            }
            if(mState.canMove(nxt) && mPrint->isWall(nxt)){
                continue;
            }
            if(mState.isPlayer(nxt)){
                suggestion.second = nxt;
                suggestion.first = (Directions)i;
                return suggestion;
            }
            if(minVal > mState.getBoardNum(nxt)){
                minVal = mState.getBoardNum(nxt);
                deltaPos = i;
                //break;
            }
        }
    }
    if(deltaPos == InvalidIndex) return suggestion;
    if(minVal == MinInitialValue) return suggestion;

    suggestion.first = DirVec[deltaPos];
    suggestion.second.row = DeltaPos[deltaPos][0] + coordinates.row;
    suggestion.second.col = DeltaPos[deltaPos][1] + coordinates.col;
    return suggestion;
}
