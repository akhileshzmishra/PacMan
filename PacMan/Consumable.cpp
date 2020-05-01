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
    mDim.dimension = Settings::getInstance()->getCoinDimension();
}

void Consumable::display(){
    mColor = Colors::CoinColor;
    mCircleDisplay.setRadius(mDim.dimension.length);
    mCircleDisplay.setFillColor(sf::Color(mColor.red, mColor.green, mColor.blue));
    mCircleDisplay.setPosition(mDim.centroid.x, mDim.centroid.y);
}


bool Consumable::makeZombie(){
    return mZombie;
}

void Consumable::makeEmpty(){
    mValue = 0;
}

ZombieMakerConsumable::ZombieMakerConsumable(DimensionMarker& dim){
    setZombie(true);
}


