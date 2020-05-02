//
//  MapDisplay.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "MapDisplay.hpp"
#include "Settings.hpp"
#include "ObjectFactory.hpp"

using namespace pacman;
using namespace pacman::impl;


MapDisplay::MapDisplay(IBluePrintPtr plan):
mPlan(plan),
mGhostWorker(plan)
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

Position MapDisplay::getPosition(){
    return Position();
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
    
                if(mPlan->getValue(i, j) == mapElements::GhostPos){
                    auto ghost = ObjectFactory::getGhost();
                    mGhostWorker.addGhost(ghost);
                    mRowCol[i][j]->setGhost(ghost);
                }
                
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

ISquarePtr MapDisplay::getSquare(Coordinates& c){
    if(mRows >= c.row || mCols >= c.col){
        return nullptr;
    }
    return mRowCol[c.row][c.col];
}

void MapDisplay::calculatePositions(){
    auto topLeft = Settings::getInstance()->getTopLeftMapPosition();
    auto square = Settings::getInstance()->getSquareDimension();
    mBBox.dimension = Settings::getInstance()->getBoardDimension();
    mRect.setPosition(topLeft.row, topLeft.col);
    Position itr = topLeft;
    for(size_t i = 0; i < mRows; i++){
        itr.row = topLeft.row;
        for(size_t j = 0; j < mCols; j++){
            mRowCol[i][j]->setPosition(itr);
            mRowCol[i][j]->setSize(square);
            itr.row += square.length;
        }
        itr.col += square.width;
    }
}

void MapDisplay::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == SquareDimensionChange){
        calculatePositions();
    }
}
