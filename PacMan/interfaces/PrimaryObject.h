//
//  PrimaryObject.h
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef PrimaryObject_h
#define PrimaryObject_h
#include "CommonIncludes.h"
#include "IRenderer.h"
namespace  pacman {
    class IPrimaryObject{
        Coordinates                    mCoOrdinates;
    public:
        virtual void setPosition(const Position& p) = 0;
        virtual Position getPosition() = 0;
        
        virtual void create() = 0;
        virtual void destroy() = 0;
        
        GENERIC_GETTER_SETTER(Coordinates, mCoOrdinates, Coordinates);
    };

    DECLARE_SHARED(IPrimaryObject);

}
#endif /* PrimaryObject_h */
