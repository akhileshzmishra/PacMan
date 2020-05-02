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
    return getNext(mMazePos);
}

void Ghost::setCoordinate(Coordinates c){
    mMazePos = c;
    Position p = Settings::getInstance()->getPositionFromCoordinates(c);
    mHead.setPosition(p.x, p.y);
}



bool Ghost::getNext(Coordinates& next){
    int altX = next.x + DeltaPos[(int)mDir][0]*mSpeed;
    int altY = next.y + DeltaPos[(int)mDir][1]*mSpeed;
    if(altX >= 0 && altY >= 0 && altX < (int) mRow && altY < (int) mCol){
        if(mBluePrint->getValue(altX, altY) != mapElements::Wall){
            next.x = altX;
            next.y = altY;
            mNextSquarePos.x = mBBox.centroid.x + DeltaPos[(int)mDir][0]*SQuareDimension.length;
            mNextSquarePos.y = mBBox.centroid.y + DeltaPos[(int)mDir][1]*SQuareDimension.width;
            return true;
        }
    }
    return false;
}

bool Ghost::move(const Position& p){
    mHead.move(p.x, p.y);
    return true;
}

void Ghost::setPosition(const Position& p){
    mBBox.centroid = p;
    mHead.setPosition(p.x, p.y);
   
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










