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
    mReady = true;
}
void PacManTheHero::PacManTheHero::destroy(){
    //mHoldingSquare = nullptr;
    //mHoldingBoard = nullptr;
    mReady = false;
}

void PacManTheHero::work(){
    if(mReady){
        move();
        
        mReady = false;
    }
    display();
}

void PacManTheHero::move(){
    bool retVal = false;
    auto mHoldingBr = mHoldingBoard.lock();
    auto sq = mHoldingBr->getSquare(getConstRefCoordinates());
    auto sqpos = sq->getPosition();
    auto& position = mBBox.referencePos;
    float r1 = position.row;
    float r2 = r1 + mBBox.dimension.width;
    float c1 = position.col;
    float c2 = c1 + mBBox.dimension.length;
    switch(mDirections){
        case pacman::UpDir:
            if(r1 < sqpos.row && r2 > sqpos.row){
                retVal = inBetweenSquaresAndGo();
            }
            else if(r2 <= sqpos.row){
                retVal = setNextSquareAndCheck();
            }
            else{
                retVal = inPresentSquareAndCheck();
            }
            break;
        case pacman::LeftDir:
            if(c1 < sqpos.col && c2 > sqpos.col){
                retVal = inBetweenSquaresAndGo();
            }
            else if(c2 <= sqpos.col){
                retVal = setNextSquareAndCheck();
            }
            else{
                retVal = inPresentSquareAndCheck();
            }
            break;
        case pacman::DownDir:
            if(r2 > sqpos.row + sSquareDim.width && r1 < sqpos.row + sSquareDim.width){
                retVal = inBetweenSquaresAndGo();
            }
            else if(r1 >= sqpos.row + sSquareDim.width){
                retVal = setNextSquareAndCheck();
            }
            else{
                retVal = inPresentSquareAndCheck();
            }
            break;
        case pacman::RightDir:
            if(c2 > sqpos.row + sSquareDim.width && c1 < sqpos.row + sSquareDim.width){
                retVal = inBetweenSquaresAndGo();
            }
            else if(c1 >= sqpos.row + sSquareDim.width){
                retVal = setNextSquareAndCheck();
            }
            else{
                retVal = inPresentSquareAndCheck();
            }
            break;
        default:
            break;
    }
}

bool PacManTheHero::setNextSquareAndCheck(){
    auto mHoldingBr = mHoldingBoard.lock();
    auto sq = mHoldingBr->getSquare(getConstRefCoordinates());
    auto coord = sq->getCopyCoordinates();
    auto oldcord = coord;
    coord.row += DeltaPos[(int)mDirections][0];
    coord.col += DeltaPos[(int)mDirections][1];
    auto next = mHoldingBr->getSquare(coord);
    if(!next){
        return false;
    }
    setCurrentSquare(next);
    mBBox.referencePos = next->getPosition();
    setCoordinates(coord);
    if(mGameState){
        mGameState->movePlayer(oldcord, coord);
        mGameState->addScore(1);
    }
    inPresentSquareAndCheck();
    return true;
}

bool PacManTheHero::inPresentSquareAndCheck(){
    auto mHoldingBr = mHoldingBoard.lock();
    auto sq = mHoldingBr->getSquare(getConstRefCoordinates());
    auto coord = sq->getCopyCoordinates();
    coord.row += DeltaPos[(int)mDirections][0];
    coord.col += DeltaPos[(int)mDirections][1];
    auto next = mHoldingBr->getSquare(coord);
    if(!next){
        return false;
    }
    if(mGameState){
        if(mGameState->isWall(coord)){
            return false;
        }
        
        if(mGameState->isGhost(coord)){
            return false;
        }
    }
    inBetweenSquaresAndGo();
    return true;
}

bool PacManTheHero::inBetweenSquaresAndGo(){
    mBBox.referencePos.row += DeltaPos[(int)mDirections][0]*mSpeed;
    mBBox.referencePos.col += DeltaPos[(int)mDirections][1]*mSpeed;
    mHead.setPosition( mBBox.referencePos.col,  mBBox.referencePos.row);
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
    if(mWin){
        mWin->draw(mHead);
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

void PacManTheHero::GetNotified(LiftData& data, const SettingsObservation& condition){
    mReady = true;
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
        mReady = false;
    }
}
