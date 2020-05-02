//
//  GhostWorker.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 02/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "GhostWorker.hpp"
#include "ghostStrategy/GhostUnchartedStrategy.hpp"
#include "ObjectFactory.hpp"
using namespace pacman;
using namespace pacman::impl;


GhostWorker::GhostWorker(IBluePrintPtr ptr):
mState(ptr),
mBluePrint(ptr){
    mStrategy = ObjectFactory::getUnchartedMoveStrategy(mState);
}

void GhostWorker::work(){
    for(size_t i = 0; i < mGhosts.size(); i++){
        if(mGhostState[i].hasReached()){
            Coordinates nxt = mStrategy->suggestNextMove(mGhosts[i]);
            if(nxt != mGhosts[i]->getRefCoordinates()){
                continue;
            }
            else{
                mGhostState[i].setnextCoordinates(nxt);
                mGhosts[i]->setCoordinates(nxt);
            }
        }
    }
}


void GhostWorker::addGhost(IGhostPtr ptr){
    if(!ptr) return;
    
    mGhosts.push_back(ptr);
    mGhostState.push_back(GhostStateOnBoard());
    mGhostState.back().setcurrPosition(ptr->getPosition());
    mGhostState.back().setcurrCoordinates(ptr->getRefCoordinates());
}
