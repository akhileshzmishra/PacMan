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

static const size_t MinInitialValue = std::numeric_limits<size_t>::max();

GhostUnchartedStrategy::GhostUnchartedStrategy(const GameState& st):
mState(st){
    mDirectionDelta = Utility::getDirectionsDelta();
}
void GhostUnchartedStrategy::setBluePrint(IBluePrintPtr ptr){
    mPrint = ptr;
}

DirSuggestion GhostUnchartedStrategy::suggestNextMove(const Coordinates& coordinates, const Directions curDir){
    DirSuggestion suggestion(InvalidDir, coordinates);
    if(!mState.isGhost(coordinates) || mState.getNeighbors(coordinates) == 0){
        return suggestion;
    }
    const Coordinates& playerCord = mState.getPlayerPosition();
    bool attackMode = false;
    if(Utility::getManhattanDistance(playerCord, coordinates) < mPursueDistance){
        attackMode = true;
    }
    if(!attackMode){
        if(mState.canGoTo(coordinates, curDir) && mState.getNeighbors(coordinates) == 2){
            Coordinates nxt;
            nxt.row = mDirectionDelta[curDir].rowDelta + coordinates.row;
            nxt.col = mDirectionDelta[curDir].colDelta + coordinates.col;
            suggestion.first = curDir;
            suggestion.second = nxt;
            return suggestion;
        }
        
        if(mState.getNeighbors(coordinates) >= 3){
            Directions xx = (Directions)(rand()%4);
            if(mState.canGoTo(coordinates, xx)){
                Coordinates nxt;
                nxt.row = mDirectionDelta[curDir].rowDelta + coordinates.row;
                nxt.col = mDirectionDelta[curDir].colDelta + coordinates.col;
                suggestion.first = curDir;
                suggestion.second = nxt;
                return suggestion;
            }
        }
    }
    Directions outDir = curDir;
    size_t minVal = MinInitialValue;
    size_t i = (size_t)curDir;
    int count = 0;
    while(count < 4){
        AutoIncrementer autoIncrementer([&i, &count]{
            i = (i + 1)%4;
            count++;
        });
        if(!mState.canGoTo(coordinates, (Directions)i)){
            continue;
        }
        Coordinates nxt;
        nxt.row = mDirectionDelta[(Directions)i].rowDelta + coordinates.row;
        nxt.col = mDirectionDelta[(Directions)i].colDelta + coordinates.col;
        
        if(mState.isPlayer(nxt)){
            suggestion.second = nxt;
            suggestion.first = (Directions)i;
            return suggestion;
        }
        if(!attackMode){
            if(minVal > mState.getBoardNum(nxt)){
                minVal = mState.getBoardNum(nxt);
                outDir = (Directions)i;
                //break;
            }
        }
        else{
            auto manDist = Utility::getManhattanDistance(nxt, playerCord);
            if(minVal > manDist){
                minVal = manDist;
                outDir = (Directions)i;
            }
        }
    }
    if(minVal == MinInitialValue) return suggestion;

    suggestion.first = mDirectionDelta[outDir].direction;
    suggestion.second.row = mDirectionDelta[outDir].rowDelta + coordinates.row;
    suggestion.second.col = mDirectionDelta[outDir].colDelta + coordinates.col;
    return suggestion;
}
