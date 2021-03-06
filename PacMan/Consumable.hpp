//
//  Consumable.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef Consumable_hpp
#define Consumable_hpp

#include "AllInterfaces.h"
#include "Settings.hpp"

namespace pacman {namespace impl{

class Consumable: public ICoin, public SettingObserver{
    int                                       mValue = 17;
    BoundingBox                               mBBox;
    sf::CircleShape                           mCircleDisplay;
    ColorRGB                                  mColor;
    bool                                      mZombie = false;
    bool                                      mRenderable = true;
    bool                                      mbCreate = false;
    int                                       manimatron = 100;
    int                                       mCounter = 100;
    float                                     mRadius = 12.0;
    bool                                      mAnimationAllowed = false;
public:
    Consumable();
    int getValue() override{
        return mValue;
    }
    
    void setValue(int s) override{
        mValue = s;
    }
    
    virtual void create() override;
    virtual void destroy() override;
    
    bool makeZombie() override;

    void makeEmpty() override;
    virtual void setPosition(const Position& p) override;
    virtual Position getPosition() override{
        return mBBox.referencePos;
    }
    
    void setZombie(bool s)                         {mZombie = s;}
    void setRenderable(bool s)override;
    
    virtual bool canBeRendered()override;
    virtual const ShapeList* getShapes()override;
    virtual DrawableObject* getShape()override;
    virtual void renderComplete()override;
    virtual void hasBeenTaken() override;
    virtual void setAnimation(bool s) override{
        mAnimationAllowed = s;
    }
    
    void GetNotified(LiftData& data, const SettingsObservation& condition) override;
private:
    void createData();
};


class ZombieMakerConsumable: public Consumable{
public:
    ZombieMakerConsumable();
};
    
}}

#endif /* Consumable_hpp */
