//
//  ScoreCard.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 08/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "ScoreCard.hpp"

using namespace pacman;
using namespace pacman::impl;

bool ScoreCard::canBeRendered(){
    return true;
}
const ShapeList* ScoreCard::getShapes(){
    return nullptr;
}
DrawableObject* ScoreCard::getShape(){
    if(gst){
        mText = "score : " + std::to_string(gst->getScore());
        mRect.setString(mText);
    }
    return &mRect;
}
void ScoreCard::renderComplete(){

}
void ScoreCard::setPosition(const Position& p){
    position = p;
}
Position ScoreCard::getPosition(){
    return position;
}

void ScoreCard::create(){
    dimension = Settings::getInstance()->getSquareDimension();
    mfont.loadFromFile("arial.ttf");
    mRect.setFont(mfont);
    mRect.setPosition(position.col, position.row);
    mRect.setFillColor(sf::Color::White);
    mRect.setOutlineThickness(1.0);
    auto squareDim = Settings::getInstance()->getSquareDimension();
    mRect.setCharacterSize(squareDim.length*0.5);
    mRect.setPosition(10.0, 10.0);
    mRect.setOutlineColor(sf::Color::Yellow);
    Settings::getInstance()->getCopyRenderer()->addRenderered(this, ForeGround);
}
void ScoreCard::destroy(){
    Settings::getInstance()->getCopyRenderer()->clearRendererd(this);
}



