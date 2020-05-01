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


MapDisplay::MapDisplay(BluePrint& plan):mPlan(plan){
    create();
}

void MapDisplay::display(){
    for(size_t i = 0; i < mRows; i++){
        for(size_t j = 0; j < mCols; j++){
            mRowCol[i][j]->display();
        }
    }
    if(getBaseFramePtr()){
        getBaseFramePtr()->draw(this);
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
    Position itr = topLeft;
    for(size_t i = 0; i < mRows; i++){
        itr.x = topLeft.x;
        for(size_t j = 0; j < mCols; j++){
            mRowCol[i][j]->setPosition(itr);
            itr.x += sq.length;
        }
        itr.y = sq.width;
    }
    
    mDimension.dimension.length = mCols*sq.length + border.length*2;
    mDimension.dimension.width = mRows*sq.width + border.width*2;
    mDimension.centroid = mDimension.dimension.length/2 + topLeft.x;
    mDimension.centroid = mDimension.dimension.width/2 + topLeft.y;
    mRect.setSize(sf::Vector2f(mDimension.dimension.length, mDimension.dimension.width));
    mRect.setFillColor(sf::Color::Blue);
}

void MapDisplay::create(){
    mRows = mPlan.getConstRefRow();
    mCols = mPlan.getConstRefCol();
    mRowCol = RowCol(mRows, OneRow(mCols, std::make_shared<SingleSquare>()));
    Position topLeft = Settings::getInstance()->getTopLeftMapPosition();
    for(size_t i = 0; i < mRows; i++){
        for(size_t j = 0; j < mCols; j++){
            mRowCol[i][j]->setType(mPlan.getValue(i, j));
            mRowCol[i][j]->create();
        }
    }
    moveTo(topLeft);
}

void MapDisplay::setBaseFrame(IBaseFrame*  ptr){
    for(size_t i = 0; i < mRows; i++){
        for(size_t j = 0; j < mCols; j++){
            mRowCol[i][j]->setBaseFrame(ptr);
        }
    }
    IDisplay::setBaseFrame(ptr);
}
