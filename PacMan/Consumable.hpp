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

class Consumable: public IGift, public SettingObserver{
    int                                       mValue = 5;
    BoundingBox                               mBBox;
    sf::CircleShape                           mCircleDisplay;
    ColorRGB                                  mColor;
    bool                                      mZombie = false;
public:
    Consumable();
    int offer() override{
        return mValue;
    }
    
    virtual void create() override;
    virtual void destroy() override;
    
    bool makeZombie() override;

    void makeEmpty() override;
    
    void display()override;
    void setZombie(bool s)                 {mZombie = s;}
    void GetNotified(LiftData& data, const SettingsObservation& condition) override;
private:
    void createData();
};


class ZombieMakerConsumable: public Consumable{
public:
    ZombieMakerConsumable(BoundingBox& dim);
};
    
}}

#endif /* Consumable_hpp */
