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

class SingleSquare: public ISquare{
    int                                       mType;
    IPlayerPtr                                mOccupant;
    BoundingBox                               mBBox;
    sf::RectangleShape                        mRect;
    ColorRGB                                  mColor;
    IGiftPtr                                  mCoin;
    bool                                      mCreate = false;
    IPlayBoard*                               mPlayBoard = nullptr;
public:
    SingleSquare(int type = mapElements::Empty);
    virtual void display() override;
    virtual bool allows() override{
        return mType != mapElements::Wall && !mOccupant;
    }
    virtual void setPosition(const Position& p)  override;
    virtual Position getPosition()  override;
    virtual void setGift(IGiftPtr ptr)override;
    virtual IGiftPtr getGift()override;
    
    virtual void setOccupant(IPlayerPtr ptr) override{
        if(ptr){
            mOccupant = ptr;
        }
    }
    
    virtual void create() override;
    virtual void destroy() override;
    virtual bool move(const Position& p) override;
    virtual void setSize(Dimension d) override;
    
    virtual void setOwner(IPlayBoard* ptr)override{
        mPlayBoard = ptr;
    }
    virtual IPlayBoard* getOwner()override{
        return mPlayBoard;
    }
    
    virtual IPlayerPtr getOccupant() override{
        return mOccupant;
    }
    
    GENERIC_GETTER_SETTER(Type,        mType,         decltype(mType));
    GENERIC_GETTER_SETTER(Dimension,   mBBox,         BoundingBox);
    
private:
    void createEmpty();
    void createWall();
    void createData();
};

DECLARE_SHARED(SingleSquare);

}}
#endif /* SingleSquare_hpp */
