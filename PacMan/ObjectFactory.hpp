//
//  ObjectFactory.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef ObjectFactory_hpp
#define ObjectFactory_hpp

#include "AllInterfaces.h"

namespace pacman {namespace impl{

class ObjectFactory{
    
public:
    static IMap* getMap();
    static IPlayer* getPlayer();
    
};
        
}}

#endif /* ObjectFactory_hpp */
