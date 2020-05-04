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

PacManTheHero::PacManTheHero(){
    SetSubject(Settings::getInstance());
    mDirectionDelta = Utility::getDirectionsDelta();
}

void PacManTheHero::setPosition(const Position& p){
    mBBox.referencePos = p;
    mHead.setPosition(p.col, p.row);
}
Position PacManTheHero::getPosition(){
    return mBBox.referencePos;
}
void PacManTheHero::create(){
    Settings::getInstance()->getCopyRenderer()->addRenderered(this, RenderLayer::ForeGround);
    mBBox.dimension = Settings::getInstance()->getGhostDimension();
    sSquareDim = Settings::getInstance()->getSquareDimension();
    mSpeed = Settings::getInstance()->getPacManSpeed();
    mHead.setPointCount(8);
    mHead.setRadius(mBBox.dimension.length);
    mHead.setFillColor(sf::Color::Yellow);
    
    Register(KeyPressedUp);
    Register(KeyPressedDown);
    Register(KeyPressedLeft);
    Register(KeyPressedRight);
    Register(SquareDimensionChange);
    //move();
    mReady = false;
}
void PacManTheHero::PacManTheHero::destroy(){
    //mHoldingSquare = nullptr;
    //mHoldingBoard = nullptr;
    //mReady = false;
    Settings::getInstance()->getCopyRenderer()->clearRendererd(this);
}

void PacManTheHero::work(){
    if(mReady){
        move();
        mReady = false;
    }
    //mGameState->print();
}

void PacManTheHero::move(){
    if(!mHoldingBoard.expired()){
        auto mHoldingBr = mHoldingBoard.lock();
        const Coordinates& currentCord = getConstRefCoordinates();
        auto nextCord = currentCord;
        nextCord.row += mDirectionDelta[mDirections].rowDelta;
        nextCord.col += mDirectionDelta[mDirections].colDelta;
        
        auto nextSquare = mHoldingBr->getSquare(nextCord);
        if(!nextSquare){
            return;
        }
        if(mGameState->isWall(nextCord)){
            return;
        }
        setPosition(nextSquare->getPosition());
        setCurrentSquare(nextSquare);
        if(mGameState){
            mGameState->movePlayer(currentCord, nextCord);
            mGameState->addScore(1);
        }
    }
}

void PacManTheHero::renderComplete(){
    
}

void PacManTheHero::setCurrentSquare(ISquarePtr ptr){
    mHoldingSquare = ptr;
}
ISquareWeakPtr PacManTheHero::getCurrentSquare(){
    return mHoldingSquare;
}
void PacManTheHero::setBoard(IPlayBoardWeakPtr ptr){
    mHoldingBoard = ptr;
}
IPlayBoardWeakPtr PacManTheHero::getBoard(){
    return mHoldingBoard;
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

void PacManTheHero::GetNotified(LiftData& data, const SettingsObservation& condition){
    
    if(condition == KeyPressedUp){
        mReady = true;
        mDirections = UpDir;
    }
    else if(condition == KeyPressedDown){
        mReady = true;
        mDirections = DownDir;
    }
    else if(condition == KeyPressedLeft){
        mReady = true;
        mDirections = LeftDir;
    }
    else if(condition == KeyPressedRight){
        mReady = true;
        mDirections = RightDir;
    }
    else{
        mBBox.dimension = Settings::getInstance()->getGhostDimension();
        sSquareDim = Settings::getInstance()->getSquareDimension();
        mReady = false;
    }
}
