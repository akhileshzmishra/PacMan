//
//  Utiliity.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 04/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef Utiliity_hpp
#define Utiliity_hpp

#include "AllInterfaces.h"
namespace pacman {namespace impl{
    
struct DirectionDelta{
    Directions   direction;
    Directions   opposite;
    int rowDelta = 0;
    int colDelta = 0;
};

    
class DirectionDeltaList{
    typedef std::vector<DirectionDelta> List;
    List mList;
public:
    DirectionDeltaList(){}
    DirectionDeltaList(List list);
    const DirectionDelta& get(Directions d);
    DirectionDelta& operator [] (Directions d);
    DirectionDelta& operator [] (int d);
    int size(){
        return (int)mList.size();
    }
};
    
class Utility{
public:
    static DirectionDeltaList getDirectionsDelta();
};

}}
#endif /* Utiliity_hpp */
