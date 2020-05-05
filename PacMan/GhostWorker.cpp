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
#include "Settings.hpp"

using namespace pacman;
using namespace pacman::impl;

Dimension GhostStateOnBoard::sSquareDim; //sGhostDim
Dimension GhostStateOnBoard::sGhostDim;

bool GhostStateOnBoard::hasReached(Directions dir){
    if(dir == Directions::UpDir){
        if(currentPos.row <= nextPos.row){
            return true;
        }
        else{
            return false;
        }
    }
    else if(dir == Directions::DownDir){
        if((currentPos.row + sSquareDim.width + mSpeed) >= (nextPos.row + sSquareDim.width)){
            return true;
        }
        else{
            return false;
        }
    }
    else if(dir == Directions::LeftDir){
        if(currentPos.col <= nextPos.col){
            return true;
        }
        else{
            return false;
        }
    }
    else if(dir == Directions::RightDir){
        if((currentPos.col + sSquareDim.length + mSpeed) >= (nextPos.col + sSquareDim.length)){
            return true;
        }
        else{
            return false;
        }
    }
    return true;
}

void GhostStateOnBoard::correctPosition(){
    currentPos = nextPos;
    mGhost->addMovable(nextPos);
}

bool GhostStateOnBoard::hasReached(){
    return hasReached(mDirection);
}

void GhostStateOnBoard::move(){
    if(mStop){
        mGhost->setPosition(currentPos);
        return;
    }
    if(mDirection >= Directions::InvalidDir){
        return;
    }
    
    mDelta.addToPositionWithSpeed(currentPos, mSpeed, mDirection);
    mGhost->addMovable(currentPos);
}


GhostWorker::GhostWorker(IBluePrintPtr ptr):
mState(ptr),
mBluePrint(ptr){
    SetSubject(Settings::getInstance());
    Register(SquareDimensionChange);
}

GhostStateOnBoard::GhostStateOnBoard(IGhostPtr ptr){
    setGhost(ptr);
    setPlayer(ptr->getBoard());
    setOwningSquare(ptr->getCurrentSquare());
    setDirection(Directions::InvalidDir);
    setcurrCoordinates(ptr->getRefCoordinates());
    settargetCoordinates(ptr->getRefCoordinates());
    setGhostDimension(Settings::getInstance()->getGhostDimension());
    setGhostDim(Settings::getInstance()->getGhostDimension());
    calculatePositions();
    mDelta = Utility::getDirectionsDelta();
}

bool GhostStateOnBoard::arrive(){
    mState->moveGhost(getConstRefcurrCoordinates()
                     , getConstReftargetCoordinates());
    if(!mPlayer.expired()){
        auto owner = mPlayer.lock();
        auto squareFrom = owner->getSquare(getRefcurrCoordinates());
        auto squareTo = owner->getSquare(getReftargetCoordinates());
        if(squareFrom == squareTo){
            return true;
        }
        
    }
    correctPosition();
    setcurrCoordinates(getReftargetCoordinates());
    mGhost->setCoordinates(getCopytargetCoordinates());
    
    return true;
}

bool GhostStateOnBoard::lookAhead(DirSuggestion& s){
    if(s.first == InvalidDir){
        return false;
    }
    settargetCoordinates(s.second);
    setDirection(s.first);
    if(!mGhost->getBoard().expired()){
        auto board = mGhost->getBoard().lock();
        auto nxtsquare = board->getSquare(s.second);
        if(nxtsquare){
            auto pos = nxtsquare->getPosition();
            settargetPosition(pos);
        }
        else{
            return false;
        }
    }
    return true;
}

void GhostStateOnBoard::calculatePositions(){
    Settings* sett = Settings::getInstance();
    auto currSquare = sett->getSquarePositionData(getRefcurrCoordinates());
    if(currSquare){
        setcurrPosition(currSquare->getRefPosition());
    }
    
    auto nextSquare = sett->getSquarePositionData(getReftargetCoordinates());
    if(nextSquare){
        settargetPosition(nextSquare->getRefPosition());
    }
}

void GhostWorker::work(){
    if(mGameEnded){
        return;
    }
    pacman::impl::LiftData ldata;
    for(size_t i = 0; i < mGhostState.size(); i++){
        if(mGhostState[i].hasReached() || !mStart){
            
            if(mState.isPlayer(mGhostState[i].getReftargetCoordinates())){
                GetSubject()->NotifyToObservers(ldata, GameHasEnded);
                mGameEnded = true;
                break;
            }
            
            if(!mGhostState[i].arrive()){
                continue;
            }
            Coordinates c = mGhostState[i].getConstRefcurrCoordinates();
            Directions d = mGhostState[i].getCopyDirection();
            if(d == Directions::InvalidDir){
                d = UpDir;
            }
            //mState.print();
            DirSuggestion nxt = mStrategy->suggestNextMove(c, d);
            if(nxt.first == Directions::InvalidDir){
                mGhostState[i].setStop(true);
                continue;
            }
            
            if(mState.isWall(nxt.second)){
                continue;
            }
            
            mGhostState[i].setDirection(nxt.first);
            
            mState.addToBoard(mGhostState[i].getConstRefcurrCoordinates(), rand()%3);
            
            if(!mGhostState[i].lookAhead(nxt)){
                mGhostState[i].setStop(true);
                continue;
            }
            
            mStart = true;
            mGhostState[i].setStop(false);
            
        }
        mGhostState[i].move();
        
    }
}

void GhostWorker::create(){
    mStrategy = ObjectFactory::getUnchartedMoveStrategy(mState);
    GhostStateOnBoard::setSquareDim(Settings::getInstance()->getSquareDimension());
    mStrategy->setBluePrint(Settings::getInstance()->getCopyBluePrint());
    mSpeed = Settings::getInstance()->getGhostSpeed();
}
void GhostWorker::destroy(){
    mStrategy = nullptr;
    for(int i = 0; i < mGhostState.size(); i++){
        mGhostState[i].destroy();
    }
    mGhostState.clear();
}


void GhostWorker::addGhost(IGhostPtr ptr){
    if(!ptr) return;
    mSpeed = Settings::getInstance()->getGhostSpeed();
    mGhostState.emplace_back(ptr);
    mGhostState.back().setSpeed(mSpeed);
    mGhostState.back().setGameState(&mState);
}

void GhostWorker::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == SquareDimensionChange){
        GhostStateOnBoard::setSquareDim(Settings::getInstance()->getSquareDimension());
        GhostStateOnBoard::setGhostDim(Settings::getInstance()->getGhostDimension());
        for(int i = 0; i < mGhostState.size(); i++){
            mGhostState[i].calculatePositions();
        }
    }
}
