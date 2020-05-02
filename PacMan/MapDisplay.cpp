//
//  MapDisplay.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "MapDisplay.hpp"
#include "Settings.hpp"

using namespace pacman;
using namespace pacman::impl;


MapDisplay::MapDisplay(IBluePrintPtr plan):
mPlan(plan)
{
    SetSubject(Settings::getInstance());
}

void MapDisplay::display(){
    if(getBaseFramePtr()){
        getBaseFramePtr()->getWindow().draw(mRect);
    }
    for(size_t i = 0; i < mRows; i++){
        for(size_t j = 0; j < mCols; j++){
            mRowCol[i][j]->display();
        }
    }
}


void MapDisplay::setPosition(const Position& p) {
    calculatePositions();
}

void MapDisplay::create(){
    setBaseFrame(Settings::getInstance()->getCopyBaseFrame());
    Register(SquareDimensionChange);
    mBBox.dimension = Settings::getInstance()->getBoardDimension();
    mRect.setSize(sf::Vector2f(mBBox.dimension.length, mBBox.dimension.width));
    if(mPlan){
        mRows = mPlan->getRow();
        mCols = mPlan->getCol();
        mRowCol = RowCol(mRows, OneRow(mCols, nullptr));
        
        for(size_t i = 0; i < mRows; i++){
            for(size_t j = 0; j < mCols; j++){
                mRowCol[i][j] = std::make_shared<SingleSquare>();
                mRowCol[i][j]->setType(mPlan->getValue(i, j));
                mRowCol[i][j]->setCoordinate(Coordinates((int)j, (int)i));
                mRowCol[i][j]->create();
            }
        }
        calculatePositions();
    }
}

void MapDisplay::destroy(){
    DeRegister(SquareDimensionChange);
    for(size_t i = 0; i < mRows; i++){
        for(size_t j = 0; j < mCols; j++){
            mRowCol[i][j]->destroy();
        }
    }
    setBaseFrame(nullptr);
}

void MapDisplay::calculatePositions(){
    auto topLeft = Settings::getInstance()->getTopLeftMapPosition();
    auto square = Settings::getInstance()->getSquareDimension();
    mBBox.dimension = Settings::getInstance()->getBoardDimension();
    mRect.setPosition(topLeft.x, topLeft.y);
    Position itr = topLeft;
    for(size_t i = 0; i < mRows; i++){
        itr.x = topLeft.x;
        for(size_t j = 0; j < mCols; j++){
            mRowCol[i][j]->setPosition(itr);
            mRowCol[i][j]->setSize(square);
            itr.x += square.length;
        }
        itr.y += square.width;
    }
}

void MapDisplay::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == SquareDimensionChange){
        calculatePositions();
    }
}
