//
//  BluePrint.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "BluePrint.hpp"

using namespace pacman;
using namespace pacman::impl;

BluePrint::BluePrint(){
    create();
}

mapElements BluePrint::getType(const Coordinates& c){
    if(c.row < mRow && c.col < mCol){
        return mMapPrint[c.row][c.col].type;
    }
    return mapElements::Invalid;
}

void BluePrint::create(){
    VecVecInt vecvecInt = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 3, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    mRow = vecvecInt.size();
    mCol = vecvecInt[0].size();
    mMapPrint = BlueNodeMatrix(mRow, BlueNodeVector(mCol));
    
    for(size_t i = 0; i < mRow; i++){
        for(size_t j = 0; j < mCol; j++){
            mMapPrint[i][j].coordinates = Coordinates((int)i, (int)j);
            mMapPrint[i][j].type = fromInteger(vecvecInt[i][j]);
            if(vecvecInt[i][j] == mapElements::Wall){
                mMapPrint[i][j].isWall = true;
            }
        }
    }
    
    
    mResolution = 4;
}

bool BluePrint::isGhost(Coordinates c) {
    return mMapPrint[c.row][c.col].type == mapElements::GhostPos;
}
bool BluePrint::isPlayer(Coordinates c){
    return mMapPrint[c.row][c.col].type == mapElements::PlayerPos;
}
bool BluePrint::isEmpty(Coordinates c){
    return mMapPrint[c.row][c.col].type == mapElements::Empty;
}
bool BluePrint::isWall(Coordinates c) {
    return mMapPrint[c.row][c.col].type == mapElements::Wall;
}

mapElements BluePrint::fromInteger(int x){
    if(x == 1){
        return mapElements::Wall;
    }
    if(x == 0){
        return mapElements::Empty;
    }
    if(x == 2){
        return mapElements::PlayerPos;
    }
    if(x == 3){
        return mapElements::GhostPos;
    }
    return mapElements::Wall;
}
