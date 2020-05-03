//
//  Ghost.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "Ghost.hpp"
#include "Settings.hpp"

using namespace pacman;
using namespace pacman::impl;

static const VecVecInt DeltaPos = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0}
};

Ghost::Ghost(){
    SetSubject(Settings::getInstance());
    setBaseFrame(Settings::getInstance()->getCopyBaseFrame());
    mBluePrint = Settings::getInstance()->getCopyBluePrint();
    mWin = &getBaseFramePtr()->getWindow();
    mRadius = mBBox.dimension.length;
}

bool Ghost::canMove(){
    return false;
}

Position Ghost::getPosition() {
    return mBBox.referencePos;
}

bool Ghost::move(const Position& p){
    mHead.move(p.row, p.col);
    return true;
}

void Ghost::setPosition(const Position& p){
    mBBox.referencePos = p;
    //mHead.setOrigin(p.col/2, p.row/2);
    mHead.setPosition(p.col, p.row);
   
}


void Ghost::create(){
    mRow = mBluePrint->getRow();
    mCol = mBluePrint->getCol();
    createData();
    Register(MainWindowDimensionChange);
}

void Ghost::createData(){
    mBBox.dimension = Settings::getInstance()->getGhostDimension();
    SQuareDimension = Settings::getInstance()->getSquareDimension();
    //mHead.setPointCount(8);
    
    mHead.setRadius(mBBox.dimension.length);
    mHead.setFillColor(sf::Color::Black);
}

void Ghost::destroy(){
    DeRegister(MainWindowDimensionChange);
}

void Ghost::live(){
    mDied = false;
}

bool Ghost::isZombie(){
    return mZombie;
}

void Ghost::setZombie(bool s){
    mZombie = s;
}


void Ghost::died(){
    mDied = true;
}

void Ghost::display(){
    mWin->draw(mHead);
}

void Ghost::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == MainWindowDimensionChange){
        createData();
    }
}


void Ghost::setCurrentSquare(ISquarePtr ptr){
    mHoldingSquare = ptr;
    if(ptr){
        ptr->setOccupant(shared_from_this());
        setCoordinates(ptr->getRefCoordinates());
        setPosition(ptr->getPosition());
    }
}


ISquareWeakPtr Ghost::getCurrentSquare(){
    return mHoldingSquare;
}


void Ghost::setBoard(IPlayBoardWeakPtr ptr){
    mHoldingBoard = ptr;
}
IPlayBoardWeakPtr Ghost::getBoard(){
    return mHoldingBoard;
}




