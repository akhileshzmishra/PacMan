//
//  CommonIncludes.h
//  PacMan
//
//  Created by Akhilesh Mishra on 29/04/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef CommonIncludes_h
#define CommonIncludes_h
#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
#include <memory>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <chrono>
#include <queue>
#include "IObserver.h"

#define GENERIC_GETTER(fnname, variable, type) \
const type& getConstRef##fnname() const { \
    return variable; \
} \
type& getRef##fnname() { \
    return variable; \
} \
type getCopy##fnname() const { \
    return variable; \
}

#define GENERIC_SETTER(fnname, variable, type) \
void set##fnname(const type t) { \
    variable = t; \
}

#define GENERIC_GETTER_SETTER(fnname, variable, type) \
GENERIC_GETTER(fnname, variable, type) \
GENERIC_SETTER(fnname, variable, type)


#define GENERIC_GETTER_SETPTR(fnname, variable, type) \
void set##fnname(type* t) { \
    variable = t; \
} \
type* get##fnname() { \
    return variable; \
}

#define DECLARE_SHARED(className) \
typedef std::shared_ptr<className> className##Ptr; \
typedef std::weak_ptr<className> className##WeakPtr;

typedef std::function<void(void)> cbackFn;

class AutoIncrementer{
    cbackFn alf;
public:
    AutoIncrementer(cbackFn f): alf(f){}
    ~AutoIncrementer(){
        alf();
    }
};



#define AUTO_SIZE_INCREMENT(fn) \
AutoIncrementer alohaIncrmenet(fn);



namespace pacman{
    
typedef std::vector<int>                   VectorInt;
typedef std::vector<VectorInt>             VecVecInt;

typedef std::vector<bool>                  VectorBool;
typedef std::vector<VectorBool>            VecVecBool;
    
typedef std::vector<size_t>                VectorSizeT;
typedef std::vector<VectorSizeT>           VecVecSizeT;

struct Coordinates{
    size_t col = 0;
    size_t row = 0;
    Coordinates(size_t ii, size_t jj){
        row = ii;
        col = jj;
    }
    Coordinates(){
        
    }
    
    bool operator == (const Coordinates& other){
        return other.row == row && other.col == col;
    }
    
    bool operator != (const Coordinates& other){
        return !(other.row == row && other.col == col);
    }
};

struct Position{
    float row = 0.0f;
    float col = 0.0f;
    Position(float xa = 0.f, float ya = 0.f){
        row = xa;
        col = ya;
    }
    
    bool operator == (const Position& other){
        return other.row == row && other.col == col;
    }
    
    bool operator != (const Position& other){
        return !(other.row == row && other.col == col);
    }
};

enum  mapElements {
    Empty                     = 0,
    Wall                      = 1,
    PlayerPos                 = 2,
    GhostPos                  = 3,
    Invalid                   = 4
};

struct Energy{
    int value = 0;
};

struct Dimension{
    float width = 0.0f;
    float length = 0.0f;
    Dimension(float x = 0.0f, float y = 0.0f){
        length = x;
        width = y;
    }
};

struct BoundingBox{
    Dimension dimension;
    Position  referencePos;
};

enum Directions{
    UpDir = 0,
    LeftDir = 1,
    DownDir = 2,
    RightDir = 3,
    InvalidDir = 4
};

struct ColorRGB{
    int red = 0;
    int green = 0;
    int blue = 0;
    ColorRGB(int r = 0, int g = 0, int b = 0):
    red(r),
    green(g),
    blue(b){
        
    }
};
namespace Colors{
    const static ColorRGB WhiteColor(225, 225, 225);
    const static ColorRGB WallColor(50, 60, 50);
    const static ColorRGB EmptyColor(152,223,138);
    const static ColorRGB CoinColor(250,189,34);
    const static ColorRGB GhostColor(143,156,208);
    const static ColorRGB BorderColor(112,50,21);
    const static ColorRGB BlackColor(0, 0, 0);
}
    
    
}//namespace pacman

#endif /* CommonIncludes_h */
