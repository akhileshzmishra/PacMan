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

bool PacManState::move(){
    if(mGameState){
        setCoordinates(mGameState->getPlayerPosition());
    }
    const Coordinates& cd = getRefCoordinates();
    if(!mGameState->canGoTo(cd, direction) || direction == InvalidDir){
        return false;
    }
    
    auto brd = getBoard().lock();
    Coordinates nextCd = currentSquare->getRefCoordinates();
    mDelta.addToCoordinate(nextCd, direction);
    ISquarePtr nxtSquare = brd->getSquare(nextCd);
    if(!nxtSquare){
        return false;
    }
    Position nxt = nxtSquare->getPosition();
    
    setCurrentSquare(nxtSquare);
    setPosition(nxt);
    mGameState->movePlayer(cd, nextCd);
    setCoordinates(nextCd);
    if(nxtSquare->getCoin()){
        int value = nxtSquare->getCoin()->getValue();
        mGameState->addScore(value);
        nxtSquare->resetCoin();
    }
    return true;
}

void PacManState::setDirection(Directions dir){
    if(direction == dir){
        if(mDirTimes >= mMaxDirTimes){
            mDirTimes = mMaxDirTimes;
        }
        else{
            mSpeed += Settings::getInstance()->getPacManSpeed();
        }
    }
    else{
        mSpeed = Settings::getInstance()->getPacManSpeed();
    }
    direction = dir;
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
        //mSignal.wait();
        mPacManThread.release();
    }
    mCreated = false;
}

void PacManTheHero::work(){
    if(mReady){
        mInternalState.move();
        mReady = false;
        mMovable = true;
        addMovable(mInternalState.getRefPosition());
    }
    else{
        addMovable(mInternalState.getRefPosition());
    }
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
    int times = 0;
    if(mMovable){
        times = 4;
    }
    RenderingJob j = {this, p, times};
    Settings::getInstance()->getCopyRenderer()->addMovable(j);
}


void PacManTheHero::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == KeyPressedUp){
        mReady = true;
        mInternalState.setDirection(UpDir);
    }
    else if(condition == KeyPressedDown){
        mReady = true;
        mInternalState.setDirection(DownDir);
    }
    else if(condition == KeyPressedLeft){
        mReady = true;
        mInternalState.setDirection(LeftDir);
    }
    else if(condition == KeyPressedRight){
        mReady = true;
        mInternalState.setDirection(RightDir);
    }
    else{
        sSquareDim = Settings::getInstance()->getSquareDimension();
        mInternalState.recalculatePosition();
        resetShape();
        mReady = false;
    }
}
