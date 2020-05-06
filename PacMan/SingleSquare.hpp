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
    BoundingBox                               mBBox;
    sf::RectangleShape                        mRect;
    sf::CircleShape                           mAnimatron;
    ColorRGB                                  mColor;
    ICoinPtr                                  mCoin;
    bool                                      mCreate = false;
    IPlayBoard*                               mPlayBoard = nullptr;
    bool                                      mRenderable = true;
    int                                       mCoinAnimation = 0;
public:
    SingleSquare(int type = mapElements::Empty);

    virtual bool allows() override{
        return mType != mapElements::Wall;
    }
    virtual void setPosition(const Position& p)  override;
    virtual Position getPosition()  override;
    virtual void setCoin(ICoinPtr ptr)override;
    virtual ICoinPtr getGift()override;
    
    virtual void create() override;
    virtual void destroy() override;

    virtual void setSize(Dimension d) override;
    
    virtual void setOwner(IPlayBoard* ptr)override{
        mPlayBoard = ptr;
    }
    virtual IPlayBoard* getOwner()override{
        return mPlayBoard;
    }
    
    virtual bool canBeRendered()override;
    virtual sf::Shape* getShape()override;
    void setRenderable(bool s) override;
    virtual const std::vector<sf::Shape*>* getShapes() override{
        return nullptr;
    }
    virtual void renderComplete() override;
    
    GENERIC_GETTER_SETTER(Type,        mType,         decltype(mType));
    GENERIC_GETTER_SETTER(Dimension,   mBBox,         BoundingBox);
    
private:
    void createEmpty();
    void createWall();
    void createData();
    void positionCoin();
    void animation();
};

DECLARE_SHARED(SingleSquare);

}}
#endif /* SingleSquare_hpp */
