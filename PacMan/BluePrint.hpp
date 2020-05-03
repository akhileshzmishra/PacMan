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
    bool        isWall         = false;
    mapElements type           = mapElements::Wall;
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
    
    mapElements getType(const Coordinates& c) override;
    
    size_t getResolution() override{
        return mResolution;
    }
    
    virtual bool isGhost(Coordinates) override;
    virtual bool isPlayer(Coordinates) override;
    virtual bool isEmpty(Coordinates) override;
    virtual bool isWall(Coordinates) override;
private:
    void create();
    mapElements fromInteger(int x);
};
    
}}

#endif /* BluePrint_hpp */
