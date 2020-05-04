//
//  Utiliity.cpp
//  PacMan
//
//  Created by Akhilesh Mishra on 04/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#include "Utiliity.hpp"

using namespace pacman;
using namespace pacman::impl;

DirectionDeltaList::DirectionDeltaList(std::vector<DirectionDelta> list):
mList(list){
    
}
const DirectionDelta& DirectionDeltaList::get(Directions d){
    return mList[(int)d];
}
DirectionDelta& DirectionDeltaList::operator [](Directions d){
    return mList[(int)d];
}

DirectionDelta& DirectionDeltaList::operator [](int d){
    return mList[d];
}

DirectionDeltaList Utility::getDirectionsDelta(){
    static DirectionDeltaList delta = {{
        {UpDir,     DownDir,    -1,  0},
        {LeftDir,   RightDir,    0, -1},
        {DownDir,   UpDir,       1,  0},
        {RightDir,  LeftDir,     0,  1}
    }};
    return delta;
}
