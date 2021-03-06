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

bool Ghost::canBeRendered(){
    return mRenderable;
}

DrawableObject* Ghost::getShape(){
    return &mHead;
}

Ghost::Ghost(){
    SetSubject(Settings::getInstance());
    mBluePrint = Settings::getInstance()->getCopyBluePrint();
    mRadius = mBBox.dimension.length;
}



Position Ghost::getPosition() {
    return mBBox.referencePos;
}



void Ghost::setPosition(const Position& p){
    mBBox.referencePos = p;
    //mHead.setOrigin(p.col/2, p.row/2);
    mHead.setPosition(p.col, p.row);
   
}
void Ghost::renderComplete(){
    
}

void Ghost::create(){
    Settings::getInstance()->getCopyRenderer()->addRenderered(this, RenderLayer::ForeGround);
    mRow = mBluePrint->getRow();
    mCol = mBluePrint->getCol();
    createData();
    Register(MainWindowDimensionChange);
}

void Ghost::createData(){
    mBBox.dimension = Settings::getInstance()->getGhostDimension();
    SQuareDimension = Settings::getInstance()->getSquareDimension();
    //mHead.setPointCount(8);
    auto color = Colors::GhostColor;
    mHead.setRadius(mBBox.dimension.length);
    mHead.setFillColor(sf::Color(color.red, color.green,color.blue));
}

void Ghost::destroy(){
    Settings::getInstance()->getCopyRenderer()->clearRendererd(this);
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


void Ghost::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == MainWindowDimensionChange){
        createData();
    }
}


void Ghost::setCurrentSquare(ISquarePtr ptr){
    mHoldingSquare = ptr;
    if(ptr){
        setCoordinates(ptr->getRefCoordinates());
        addMovable(ptr->getPosition());
    }
}

void Ghost::addMovable(const Position& p)
{
    RenderingJob j = {this, p, 0};
    Settings::getInstance()->getCopyRenderer()->addMovable(j);
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




