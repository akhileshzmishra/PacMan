//
//  IBluePrint.h
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IBluePrint_h
#define IBluePrint_h
#include "CommonIncludes.h"
namespace  pacman {

    class IBluePrint{
    public:
        virtual ~IBluePrint(){}
        virtual size_t getRow() const= 0;
        virtual size_t getCol() const= 0;
        virtual size_t getResolution() const= 0;
        virtual mapElements getType(const Coordinates& c) const = 0;
        
        virtual bool isGhost(const Coordinates&) const  = 0;
        virtual bool isPlayer(const Coordinates&) const  = 0;
        virtual bool isEmpty(const Coordinates&)  const  = 0;
        virtual bool isWall(const Coordinates&) const  = 0;
    };
    
    DECLARE_SHARED(IBluePrint);
}
#endif /* IBluePrint_h */
