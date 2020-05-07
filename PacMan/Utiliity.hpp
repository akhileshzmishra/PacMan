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
#include "BlockingQueue.h"
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
    void addToCoordinate(Coordinates& c, Directions d);
    void addToPositionWithSpeed(Position& p, float speed, Directions d);
};
    
class Utility{
public:
    static DirectionDeltaList getDirectionsDelta();
    static size_t getManhattanDistance(const Coordinates& a, const Coordinates& b){
        size_t rres;
        size_t cres;
        if(a.row > b.row){
            rres = a.row - b.row;
        }
        else{
            rres = b.row - a.row;
        }
        
        if(a.col > b.col){
            cres = a.col - b.col;
        }
        else{
            cres = b.col - a.col;
        }
        
        return rres + cres;
    }
};

}}
#endif /* Utiliity_hpp */
