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
}

void PacManTheHero::setPosition(const Position& p){
    mBBox.referencePos = p;
    mHead.setPosition(p.col, p.row);
}
Position PacManTheHero::getPosition(){
    return mBBox.referencePos;
}
void PacManTheHero::create(){
    mBBox.dimension = Settings::getInstance()->getGhostDimension();
    sSquareDim = Settings::getInstance()->getSquareDimension();
    mSpeed = Settings::getInstance()->getPacManSpeed();
    mHead.setPointCount(8);
    mHead.setRadius(mBBox.dimension.length);
    mHead.setFillColor(sf::Color::Yellow);
    
    setBaseFrame(Settings::getInstance()->getCopyBaseFrame());
    mWin = &getBaseFramePtr()->getWindow();
    
    Register(KeyPressedUp);
    Register(KeyPressedDown);
    Register(KeyPressedLeft);
    Register(KeyPressedRight);
    Register(SquareDimensionChange);
}
void PacManTheHero::PacManTheHero::destroy(){
    //mHoldingSquare = nullptr;
    //mHoldingBoard = nullptr;
}

void PacManTheHero::work(){
    move();
    display();
}

bool PacManTheHero::reached(){
    return false;
}

void PacManTheHero::move(){
    if(canMove()){
        
    }
    if(!mHoldingBoard.expired()){
        auto mHoldingBr = mHoldingBoard.lock();
        auto sq = mHoldingBr->getSquare(getConstRefCoordinates());
        if(sq){
            setPosition(sq->getPosition());
        }
    }
}

bool PacManTheHero::canMove(){
    auto& currentPos = mBBox.referencePos;
    bool canmoveTo = false;
    if(mDirections == Directions::UpDir){
        canmoveTo = (currentPos.row <= mNextPos.row);
    }
    else if(mDirections == Directions::DownDir){
        canmoveTo = (currentPos.row + sSquareDim.width + mSpeed) >= (mNextPos.row + sSquareDim.width);
    }
    else if(mDirections == Directions::LeftDir){
        canmoveTo = (currentPos.col <= mNextPos.col);
    }
    else if(mDirections == Directions::RightDir){
        canmoveTo = (currentPos.col + sSquareDim.length + mSpeed) >= (mNextPos.col + sSquareDim.length);
    }
    return true;
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

void PacManTheHero::display(){
    mWin->draw(mHead);
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

void PacManTheHero::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == KeyPressedUp){
        mDirections = UpDir;
    }
    else if(condition == KeyPressedDown){
        mDirections = DownDir;
    }
    else if(condition == KeyPressedLeft){
        mDirections = LeftDir;
    }
    else if(condition == KeyPressedRight){
        mDirections = RightDir;
    }
    else{
        mBBox.dimension = Settings::getInstance()->getGhostDimension();
        sSquareDim = Settings::getInstance()->getSquareDimension();
    }
}
