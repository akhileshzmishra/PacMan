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

class BluePrint{
    VecVecInt                                 mMapPrint;
    size_t                                    mRow;
    size_t                                    mCol;
public:
    BluePrint();
    GENERIC_GETTER(Row, mRow, decltype(mRow));
    GENERIC_GETTER(Col, mCol, decltype(mCol));
    int getValue(size_t r, size_t c){
        if(r < mRow && c < mCol){
            return mMapPrint[r][c];
        }
        return -1;
    }
private:
    void create();
};
    
}}

#endif /* BluePrint_hpp */
