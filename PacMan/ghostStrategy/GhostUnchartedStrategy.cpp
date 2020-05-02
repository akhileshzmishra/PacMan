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

static const VecVecInt DeltaPos = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0}
};

GhostUnchartedStrategy::GhostUnchartedStrategy(GameState& st):
mState(st){
    
}
void GhostUnchartedStrategy::setBluePrint(IBluePrintPtr ptr){
    mPrint = ptr;
}
Coordinates GhostUnchartedStrategy::suggestNextMove(IGhostPtr ptr){
    auto coordinates = ptr->getRefCoordinates();
    if(!mState.isGhost(coordinates)){
        return coordinates;
    }
    size_t deltaPos = 5;
    int minVal = std::numeric_limits<int>::min();
    for(size_t i = 0; i < DeltaPos.size(); i++){
        Coordinates nxt;
        nxt.row = DeltaPos[i][0] + coordinates.row;
        nxt.col = DeltaPos[i][1] + coordinates.col;
        if(nxt.row < mState.getRows() && nxt.col < mState.getCols()){
            if(minVal > mState.getBoardNum(nxt)){
                minVal = mState.getBoardNum(nxt);
                deltaPos = i;
            }
        }
    }
    if(deltaPos == 5) return coordinates;
    Coordinates nxt;
    nxt.row = DeltaPos[deltaPos][0] + coordinates.row;
    nxt.col = DeltaPos[deltaPos][1] + coordinates.col;
    return nxt;
}
