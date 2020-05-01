//
//  Settings.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "Settings.hpp"

using namespace pacman;
using namespace pacman::impl;

Settings::Settings(){
    
}

Settings* Settings::getInstance(){
    static Settings settings;
    return &settings;
}


Dimension Settings::getCoinDimension(){
    static Dimension dim(4.0, 4.0);
    return dim;
}

Dimension Settings::getSquareDimension(){
    static Dimension dim(8.0, 8.0);
    return dim;
}

Dimension Settings::getBoardDimension(){
    static Dimension dim(1080.0, 780.0);
    return dim;
}

Dimension Settings::getWindowDimension(){
    static Dimension dim(1080, 1080);
    return dim;
}

Position Settings::getTopLeftMapPosition(){
    static Position pos(10.0, 10.0);
    return pos;
}


Dimension Settings::getBoardBorders(){
    static Dimension dim(2.0, 2.0);
    return dim;
}

ColorRGB Settings::getBoardColor(){
    return Colors::WallColor;
}

ColorRGB Settings::getEmptyColor(){
    return Colors::EmptyColor;
}

ColorRGB Settings::getWallColor(){
    return Colors::WallColor;
}

ColorRGB Settings::getCoinColor(){
    return Colors::CoinColor;
}
