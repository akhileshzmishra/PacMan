//
//  IDisplay.h
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IDisplay_h
#define IDisplay_h
#include "PrimaryObject.h"
#include "GraphicIncludes.h"

namespace  pacman {
    
class IStaticObjects: public IPrimaryObject{
public:
    virtual bool canMove(){
        return false;
    }
    
    
};
DECLARE_SHARED(IStaticObjects);
    
    
    
}



#endif /* IDisplay_h */
