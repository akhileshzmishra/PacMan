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

namespace pacman {namespace impl{

class Consumable: public IGift{
    int                                       mValue = 5;
    DimensionMarker                           mDim;
    sf::CircleShape                           mCircleDisplay;
    ColorRGB                                  mColor;
    bool                                      mZombie = false;
public:
    Consumable();
    int offer() override{
        return mValue;
    }
    
    bool makeZombie() override;

    void makeEmpty() override;
    
    void display()override;
    void setZombie(bool s)                 {mZombie = s;}
    
    sf::Shape* getShape() override{
        return &mCircleDisplay;
    }
};


class ZombieMakerConsumable: public Consumable{
public:
    ZombieMakerConsumable(DimensionMarker& dim);
};
    
}}

#endif /* Consumable_hpp */
