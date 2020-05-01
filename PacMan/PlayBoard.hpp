//
//  ConcreteMap.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef ConcreteMap_hpp
#define ConcreteMap_hpp

#include "AllInterfaces.h"
#include "MapDisplay.hpp"
#include "BluePrint.hpp"

namespace pacman {namespace impl{


typedef std::vector<IEnemyPtr> Enemies;
class PlayBoard: public IPlayBoard{
    MapDisplayPtr                             mDisplay;
    Enemies                                   mEnemies;
    IHeroPtr                                  mPlayer;
    IBluePrintPtr                             mBluePrint;
    DimensionMarker                           mDimension;
    bool                                      mSetup = false;
public:
    PlayBoard();
    GENERIC_GETTER_SETTER(SquareDim,   mDimension,    DimensionMarker);
    virtual void display() override;
    virtual void create() override;
    virtual void destroy() override;
    virtual void setPosition(const Position& p) override;
};



}}



#endif /* ConcreteMap_hpp */
