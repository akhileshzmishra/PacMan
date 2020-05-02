//
//  BluePrint.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef BluePrint_hpp
#define BluePrint_hpp

#include "AllInterfaces.h"

namespace pacman {namespace impl{
    
struct BluePrintNode{
    bool isWall = false;
    int type     = mapElements::Wall;
    Coordinates coordinates;
    Position    position;
    Dimension   dimension;
};
typedef std::vector<BluePrintNode>            BlueNodeVector;
typedef std::vector<BlueNodeVector>           BlueNodeMatrix;

class BluePrint: public IBluePrint{
    BlueNodeMatrix                            mMapPrint;
    size_t                                    mRow;
    size_t                                    mCol;
    size_t                                    mResolution;
public:
    BluePrint();
    size_t getRow() override{
        return mRow;
    }
    size_t getCol() override{
        return mCol;
    }
    int getValue(size_t r, size_t c) override;
    
    size_t getResolution() override{
        return mResolution;
    }
private:
    void create();
};
    
}}

#endif /* BluePrint_hpp */
