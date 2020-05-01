//
//  SingleSquare.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef SingleSquare_hpp
#define SingleSquare_hpp
#include "AllInterfaces.h"
#include "Consumable.hpp"

namespace pacman {namespace impl{

class SingleSquare: public ISquare, public SettingObserver{
    int                                       mType;
    IPlayerPtr                                mOccupant;
    DimensionMarker                           mDimension;
    sf::RectangleShape                        mRect;
    ColorRGB                                  mColor;
    IGiftPtr                                  mCoin;
    bool                                      mCreate = false;
public:
    SingleSquare(int type = mapElements::Empty);
    virtual void display() override;
    virtual bool allows() override{
        return mType != mapElements::Wall;
    }
    virtual void setPosition(const Position& p)  override;
    virtual void setGift(IGiftPtr ptr)override;
    virtual IGiftPtr getGift()override;
    
    virtual void create() override;
    virtual void destroy() override;
    
    GENERIC_GETTER_SETTER(Type,        mType,         decltype(mType));
    GENERIC_GETTER_SETTER(Occupant,    mOccupant,     IPlayerPtr);
    GENERIC_GETTER_SETTER(Dimension,   mDimension,    DimensionMarker);
    
    void GetNotified(LiftData& data, const SettingsObservation& condition) override;
private:
    void createEmpty();
    void createWall();
    void createData();
};

DECLARE_SHARED(SingleSquare);

}}
#endif /* SingleSquare_hpp */
