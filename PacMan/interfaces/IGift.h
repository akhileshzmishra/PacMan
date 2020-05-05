//
//  IBluePrint.h
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IGift_HPPPDP___
#define IGift_HPPPDP___
#include "IStaticObjects.h"

namespace  pacman {

    class IGift: public IStaticObjects{
    public:
        virtual ~IGift(){}
        virtual int offer() = 0;
        virtual bool makeZombie() = 0;
        virtual void makeEmpty() = 0;
    };

    DECLARE_SHARED(IGift);

}

#endif /* IBluePrint_h */
