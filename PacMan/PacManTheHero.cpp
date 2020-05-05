//
//  PacManTheHero.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 03/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "PacManTheHero.hpp"
using namespace pacman;
using namespace pacman::impl;

static Dimension sSquareDim = Settings::getInstance()->getSquareDimension();

PacManState::PacManState(){
    mDelta = Utility::getDirectionsDelta();
}

void PacManState::move(){
    if(mGameState){
        setCoordinates(mGameState->getPlayerPosition());
    }
    const Coordinates& cd = getRefCoordinates();
    if(!mGameState->canGoTo(cd, direction) || direction == InvalidDir){
        return;
    }
    
    if(!examineIfReached()){
        mDelta.addToPositionWithSpeed(currentPosition, mSpeed, direction);
    }
}

bool PacManState::examineIfReached(){
    auto brd = getBoard().lock();
    const Coordinates& cd = getRefCoordinates();
    Coordinates nextCd = currentSquare->getRefCoordinates();
    mDelta.addToCoordinate(nextCd, direction);
    ISquarePtr nxtSquare = brd->getSquare(nextCd);
    if(!nxtSquare){
        return false;
    }
    Position nxt = nxtSquare->getPosition();
    Position currSqPos = currentSquare->getPosition();
    bool reached = false;
    Position speedPos;
    mDelta.addToPositionWithSpeed(speedPos, mSpeed, direction);
    switch(direction){
        case UpDir:
            if(currentPosition.row + sSquareDim.width + speedPos.row <= currSqPos.row){
                setPosition(nxt);
                reached = true;
            }
            break;
        case LeftDir:
            if(currentPosition.col + sSquareDim.length + speedPos.col <= currSqPos.col ){
                setPosition(nxt);
                reached = true;
            }
            break;
        case DownDir:
            if(currentPosition.row + speedPos.row >= nxt.row){
                setPosition(nxt);
                reached = true;
            }
            break;
        case RightDir:
            if(currentPosition.col + speedPos.col  >= nxt.col){
                setPosition(nxt);
                reached = true;
            }
            break;
        default:
            break;
    }
    if(reached){
        setCurrentSquare(nxtSquare);
        mGameState->movePlayer(cd, nextCd);
        setCoordinates(nextCd);
    }
    //nxtSquare->setRenderable(true);
    //currentSquare->setRenderable(true);
    return reached;
}

void PacManState::recalculatePosition(){
    auto square = getCopyCurrentSquare();
    if(square){
        setPosition(square->getPosition());
        setCoordinates(square->getCopyCoordinates());
    }
    setDimension(sSquareDim);
}

PacManTheHero::PacManTheHero(){
    SetSubject(Settings::getInstance());
    
}

PacManTheHero::~PacManTheHero(){
    destroy();
}

void PacManTheHero::setPosition(const Position& p){
    mInternalState.setPosition(p);
    mHead.setPosition(p.col, p.row);
}


Position PacManTheHero::getPosition(){
    return mInternalState.getRefPosition();
}


void PacManTheHero::create(){
    //Settings::getInstance()->getCopyRenderer()->addRenderered(this, RenderLayer::ForeGround);
    sSquareDim = Settings::getInstance()->getSquareDimension();
    mInternalState.setSpeed(Settings::getInstance()->getPacManSpeed());
    
    mInternalState.recalculatePosition();
    
    
    resetShape();
    
    Register(KeyPressedUp);
    Register(KeyPressedDown);
    Register(KeyPressedLeft);
    Register(KeyPressedRight);
    Register(SquareDimensionChange);
    
    mPacManThread.reset(new std::thread([this]{
        while(mContinueThread){
            auto value = mQueue.pop();
            if(!value.second){
                continue;
            }
            mInternalState.setDirections(value.first);
            int diff = 100;
            for(int i = 0; i < diff; i++){
               
                mInternalState.move();
                //mHead.setPosition(mInternalState.getRefPosition().col, mInternalState.getRefPosition().row);
                mReady = false;
                //mInternalState.getGameState()->print();
                addMovable(mInternalState.getRefPosition());
            }
            mSignal.signal();
        }
    }));
    mCreated = true;
    mReady = false;
}

void PacManTheHero::resetShape(){
    mHead.setPointCount(8);
    mHead.setRadius(mInternalState.getRefDimension().length/2);
    mHead.setFillColor(sf::Color::Yellow);
    mHead.setPosition(mInternalState.getRefPosition().col, mInternalState.getRefPosition().row);
}


void PacManTheHero::PacManTheHero::destroy(){
    if(mCreated){
        mContinueThread = false;
        mSignal.wait();
        mPacManThread.release();
    }
    mCreated = false;
}

void PacManTheHero::work(){
    addMovable(mInternalState.getRefPosition());
}

void PacManTheHero::renderComplete(){
    
}

void PacManTheHero::setCurrentSquare(ISquarePtr ptr){
    mInternalState.setCoordinates(ptr->getCopyCoordinates());
    mInternalState.setCurrentSquare(ptr);
    mInternalState.setPosition(ptr->getPosition());
    sSquareDim = Settings::getInstance()->getSquareDimension();
}

ISquareWeakPtr PacManTheHero::getCurrentSquare(){
    return mInternalState.getCopyCurrentSquare();
}

void PacManTheHero::setBoard(IPlayBoardWeakPtr ptr){
    mInternalState.setPlayboard(ptr);
}

IPlayBoardWeakPtr PacManTheHero::getBoard(){
    return mInternalState.getBoard();
}

void PacManTheHero::died(){
    mIsDead = true;
    if(mLives > 0){
        mLives--;
    }
}
void PacManTheHero::live(){
    if(mLives > 0){
        mIsDead = false;
    }
    else{
        mIsDead = true;
    }
}

void PacManTheHero::addEnergy(const Energy& e){
    mEnergy.value += e.value;
    if(mEnergy.value >= 50){
        mHasSuperPowers = true;
    }
}

bool PacManTheHero::canKill(){
    return mHasSuperPowers;
}

void PacManTheHero::kill(){
    
}

bool PacManTheHero::canBeRendered(){
    
    return mRenderable;
}

sf::Shape* PacManTheHero::getShape(){
    return &mHead;
}

void PacManTheHero::addMovable(const Position& p)
{
    RenderingJob j = {this, p, 0.0, false};
    Settings::getInstance()->getCopyRenderer()->addMovable(j);
}

void PacManTheHero::addMovable(const Position& p, float speed)
{
    RenderingJob j = {this, p, speed, true};
    Settings::getInstance()->getCopyRenderer()->addMovable(j);
}

void PacManTheHero::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == KeyPressedUp){
        mReady = true;
        mQueue.push(UpDir);
    }
    else if(condition == KeyPressedDown){
        mReady = true;
        mQueue.push(DownDir);
    }
    else if(condition == KeyPressedLeft){
        mReady = true;
        mQueue.push(LeftDir);
    }
    else if(condition == KeyPressedRight){
        mReady = true;
        mQueue.push(RightDir);
    }
    else{
        sSquareDim = Settings::getInstance()->getSquareDimension();
        mInternalState.recalculatePosition();
        resetShape();
        mReady = false;
    }
}
