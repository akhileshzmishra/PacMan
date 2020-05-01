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
}

void MapDisplay::display(){
    if(getBaseFramePtr()){
        //getBaseFramePtr()->getWindow().draw(mRect);
    }
    for(size_t i = 0; i < mRows; i++){
        for(size_t j = 0; j < mCols; j++){
            mRowCol[i][j]->display();
        }
    }
}


void MapDisplay::setPosition(const Position& p) {
    Position topLeft;
    topLeft.x =  mDimension.dimension.length/2 - p.x;
    topLeft.y = mDimension.dimension.width/2 - p.y;
    moveTo(topLeft);
}

void MapDisplay::moveTo(Position topLeft){
    Dimension sq = Settings::getInstance()->getSquareDimension();
    Dimension border = Settings::getInstance()->getBoardBorders();
    mDimension.dimension.length = mCols*sq.length + border.length*2;
    mDimension.dimension.width = mRows*sq.width + border.width*2;
    mDimension.centroid = mDimension.dimension.length/2 + topLeft.x;
    mDimension.centroid = mDimension.dimension.width/2 + topLeft.y;
    mRect.setSize(sf::Vector2f(mDimension.dimension.length, mDimension.dimension.width));
    //mRect.setFillColor(sf::Color::Black);
    
    Position itr = topLeft;
    for(size_t i = 0; i < mRows; i++){
        itr.x = topLeft.x;
        for(size_t j = 0; j < mCols; j++){
            mRowCol[i][j]->setPosition(itr);
            itr.x += sq.length;
        }
        itr.y += sq.width;
    }
}

void MapDisplay::create(){
    Position topLeft = Settings::getInstance()->getTopLeftMapPosition();
    setBaseFrame(Settings::getInstance()->getCopyBaseFrame());
    Dimension sq = Settings::getInstance()->getSquareDimension();
    Dimension border = Settings::getInstance()->getBoardBorders();
    mDimension.dimension.length = mCols*sq.length + border.length*2;
    mDimension.dimension.width = mRows*sq.width + border.width*2;
    mDimension.centroid = mDimension.dimension.length/2 + topLeft.x;
    mDimension.centroid = mDimension.dimension.width/2 + topLeft.y;
    mRect.setSize(sf::Vector2f(mDimension.dimension.length, mDimension.dimension.width));
    if(mPlan){
        mRows = mPlan->getRow();
        mCols = mPlan->getCol();
        mRowCol = RowCol(mRows, OneRow(mCols, std::make_shared<SingleSquare>()));
        
        Position itr = topLeft;
        for(size_t i = 0; i < mRows; i++){
            itr.x = topLeft.x;
            for(size_t j = 0; j < mCols; j++){
                mRowCol[i][j]->setPosition(itr);
                itr.x += sq.length;
                mRowCol[i][j]->setType(mPlan->getValue(i, j));
                mRowCol[i][j]->create();
            }
            itr.y += sq.width;
        }
    }
}

void MapDisplay::destroy(){
    for(size_t i = 0; i < mRows; i++){
        for(size_t j = 0; j < mCols; j++){
            mRowCol[i][j]->destroy();
        }
    }
    setBaseFrame(nullptr);
}
