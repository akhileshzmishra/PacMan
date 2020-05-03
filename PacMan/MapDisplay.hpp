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
#include "GhostWorker.hpp"

namespace pacman {namespace impl{

class MapDisplay: public IPlayBoard, public SettingObserver{
    typedef std::vector<SingleSquarePtr>      OneRow;
    typedef std::vector<OneRow>               RowCol;
    RowCol                                    mRowCol;
    IBluePrintPtr                             mPlan;
    size_t                                    mRows;
    size_t                                    mCols;
    BoundingBox                               mBBox;
    sf::RectangleShape                        mRect;
    IPacManPtr                                mPlayer;
    
public:
    MapDisplay(IBluePrintPtr plan);
    virtual void display() override;
    void setPosition(const Position& p)  override;
    Position getPosition() override;
    
    virtual void create() override;
    virtual void destroy() override;
    virtual ISquarePtr getSquare(const Coordinates& c)override;
    
    GENERIC_GETTER_SETTER(Rows,        mRows,         decltype(mRows));
    GENERIC_GETTER_SETTER(Cols,        mCols,         decltype(mCols));
    GENERIC_GETTER_SETTER(SquareDim,   mBBox,         BoundingBox);
    
    void GetNotified(LiftData& data, const SettingsObservation& condition) override;
private:
    void calculatePositions();
};

DECLARE_SHARED(MapDisplay);

}}
#endif /* MapDisplay_hpp */
