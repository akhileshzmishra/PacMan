//
//  MapDisplay.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef MapDisplay_hpp
#define MapDisplay_hpp

#include "AllInterfaces.h"
#include "SingleSquare.hpp"
#include "BluePrint.hpp"

namespace pacman {namespace impl{

class MapDisplay: public IDisplay{
    typedef std::vector<SingleSquarePtr>      OneRow;
    typedef std::vector<OneRow>               RowCol;
    RowCol                                    mRowCol;
    IBluePrintPtr                             mPlan;
    size_t                                    mRows;
    size_t                                    mCols;
    DimensionMarker                           mDimension;
    sf::RectangleShape                        mRect;
public:
    MapDisplay(IBluePrintPtr plan);
    virtual void display() override;
    void setPosition(const Position& p)  override;
    virtual void setDirection(Directions d) override{
        (void)d;
    }
    virtual void setSpeed(size_t speed) override{
        (void)speed;
    }
    
    virtual void create() override;
    virtual void destroy() override;
    
    GENERIC_GETTER_SETTER(Rows,        mRows,         decltype(mRows));
    GENERIC_GETTER_SETTER(Cols,        mCols,         decltype(mCols));
    GENERIC_GETTER_SETTER(SquareDim,   mDimension,    DimensionMarker);
private:
    
    void moveTo(Position topLeft);
};

DECLARE_SHARED(MapDisplay);

}}
#endif /* MapDisplay_hpp */
