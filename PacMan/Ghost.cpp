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
    mHead.setPosition(p.row, p.col);
   
}

void Ghost::setSpeed(size_t speed){
    mSpeed = (int) speed;
}

void Ghost::create(){
    mRow = mBluePrint->getRow();
    mCol = mBluePrint->getCol();
    createData();
    Register(MainWindowDimensionChange);
}

void Ghost::createData(){
    mBBox.dimension = Settings::getInstance()->getCoinDimension();
    SQuareDimension = Settings::getInstance()->getSquareDimension();
    mHead.setPointCount(8);
    mHead.setRadius(mBBox.dimension.length);
    mHead.setFillColor(sf::Color::Blue);
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
    if(getBaseFramePtr()){
        getBaseFramePtr()->getWindow().draw(mHead);
    }
}

void Ghost::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == MainWindowDimensionChange){
        createData();
    }
}


void Ghost::setCurrentSquare(ISquarePtr ptr){
    mHoldingSquare = ptr;
}


ISquarePtr Ghost::getCurrentSquare(){
    return mHoldingSquare;
}







