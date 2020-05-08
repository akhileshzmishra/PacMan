//
//  Consumable.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "Consumable.hpp"
#include "Settings.hpp"

using namespace pacman;
using namespace pacman::impl;

Consumable::Consumable(){
    SetSubject(Settings::getInstance());
}


bool Consumable::makeZombie(){
    return mZombie;
}

void Consumable::makeEmpty(){
    mValue = 0;
}

void Consumable::setPosition(const Position& p){
    mBBox.referencePos = p;
    createData();
}

bool Consumable::canBeRendered(){
    return mRenderable;
}

const ShapeList* Consumable::getShapes(){
    return nullptr;
}
sf::Shape* Consumable::getShape(){
    if(mAnimationAllowed){
        if(manimatron > 0){
            manimatron--;
            mCircleDisplay.setRadius(mRadius + 0.01*manimatron);
        }
        else if(manimatron <= -100){
            manimatron = 100;
        }
        else{
            manimatron--;
            mCircleDisplay.setRadius(mRadius + 0.01*manimatron);
        }
    }
    return &mCircleDisplay;
}
void Consumable::renderComplete(){
    
}

void Consumable::hasBeenTaken(){
    auto pos = getPosition();
    pacman::RenderingJob job = {this, pos, 100};
    
    for(int i = 0; i < 1; i++){
        pos.row -= 100;
        Settings::getInstance()->getCopyRenderer()->addMovable(job);
    }
    Settings::getInstance()->getCopyRenderer()->clearRendererd(this);
}

ZombieMakerConsumable::ZombieMakerConsumable(){
    setZombie(true);
    setAnimation(true);
}

void Consumable::createData(){
    mColor = Colors::CoinColor;
    mBBox.dimension = Settings::getInstance()->getCoinDimension();
    mCircleDisplay.setRadius(mBBox.dimension.length/2);
    mRadius = mBBox.dimension.length/2;
    mCircleDisplay.setFillColor(sf::Color(mColor.red, mColor.green, mColor.blue));
    mCircleDisplay.setPosition(mBBox.referencePos.col, mBBox.referencePos.row);
    mCircleDisplay.setOutlineThickness(2.0);
    //mAnimationAllowed = Settings::getInstance()->getCopycoinAnimation();
}
void Consumable::create(){
    if(mbCreate) return;
    Settings::getInstance()->getCopyRenderer()->addRenderered(this, Middleground);
    createData();
    Register(CoinDimensionChange);
    mbCreate = true;
}

void Consumable::destroy(){
    if(mbCreate){
        Settings::getInstance()->getCopyRenderer()->clearRendererd(this);
        DeRegister(CoinDimensionChange);
    }
    mbCreate = false;
}

void Consumable::GetNotified(LiftData& data, const SettingsObservation& condition){
    if(condition == MainWindowDimensionChange){
        mBBox.dimension = Settings::getInstance()->getCoinDimension();
        createData();
    }
}

