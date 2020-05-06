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
#include "IRenderer.h"

namespace  pacman {

    class ICoin: public IStaticObjects, public IRenderered{
    public:
        virtual ~ICoin(){}
        virtual int getValue() = 0;
        virtual void setValue(int s) = 0;
        virtual bool makeZombie() = 0;
        virtual void makeEmpty() = 0;
        virtual void setRenderable(bool s) = 0;
    };

    DECLARE_SHARED(ICoin);

}

#endif /* IBluePrint_h */
