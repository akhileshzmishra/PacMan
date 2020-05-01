//
//  IPlayer.h
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IPlayer_h
#define IPlayer_h
#include "IDisplay.h"
namespace  pacman {
    class IPlayer: public IDisplay{
    public:
        virtual bool canMove() override{
            return true;
        }
        
    };

    DECLARE_SHARED(IPlayer);


    class IEnemy: public IPlayer{
    public:
        virtual void canEat() = 0;
        virtual void isZombie() = 0;
        virtual void canChase() = 0;
        virtual bool eat() = 0;
        
    };

    DECLARE_SHARED(IEnemy);


    class IHero: public IPlayer{
        virtual void consume(const Energy& e) = 0;
        virtual void canKill() = 0;
        virtual void kill() = 0;
    };

    DECLARE_SHARED(IHero);
}

#endif /* IPlayer_h */
