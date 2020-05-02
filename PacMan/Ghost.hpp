//
//  Ghost.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef Ghost_hpp
#define Ghost_hpp

#include "AllInterfaces.h"
#include "GraphicIncludes.h"
#include "Settings.hpp"

namespace pacman {namespace impl{
class Ghost:public IGhost, public SettingObserver{
    sf::CircleShape                 mHead;
    BoundingBox                     mBBox;
    int                             mSpeed = 1;
    bool                            mZombie = false;
    bool                            mDied = false;
    IBluePrintPtr                   mBluePrint;
    Directions                      mDir = Directions::UpDir;
    Coordinates                     mMazePos;
    size_t                          mRow;
    size_t                          mCol;
    Dimension                       SQuareDimension;
    Position                        mNextSquarePos;
    ISquarePtr                      mHoldingSquare;
public:
    Ghost();
    virtual bool canMove() override;
    virtual void setDirection(Directions d) override{
        mDir = d;
    }
    
    virtual bool move(const Position& p)override;
    virtual void setPosition(const Position& p)override;
    virtual Position getPosition() override;
    virtual void setSpeed(size_t speed)override;
    virtual void create()override;
    virtual void destroy()override;
    virtual void setCurrentSquare(ISquarePtr)override;
    virtual ISquarePtr getCurrentSquare()override;
    
    virtual void live()override;
    virtual bool isZombie()override;
    virtual void setZombie(bool s)override;
    virtual void died()override;
    virtual void display()override;
    
    void GetNotified(LiftData& data, const SettingsObservation& condition) override;
    
private:
    void createData();
};

DECLARE_SHARED(Ghost);

}}

#endif /* Ghost_hpp */
