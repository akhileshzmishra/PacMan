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
    
class IDisplay: public IPrimaryObject{
public:
    virtual bool canMove() override{
        return false;
    }
    virtual bool move() override{
        return false;
    }
    virtual void display() = 0;
    
    virtual sf::Shape* getShape(){
        return nullptr;
    }
    
};
DECLARE_SHARED(IDisplay);
    
    
    
}



#endif /* IDisplay_h */
