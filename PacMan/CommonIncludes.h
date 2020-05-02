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
#include "IObserver.h"

#define GENERIC_GETTER(fnname, variable, type) \
const type& getConstRef##fnname() { \
    return variable; \
} \
type& getRef##fnname() { \
    return variable; \
} \
type getCopy##fnname() { \
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

namespace  mapElements {
    const int Empty                     = 0;
    const int Wall                      = 1;
    const int StartPos                  = 2;
    const int GhostPos                  = 3;
    const int PlayerPos                 = 4;
    const int Invalid                   = 5;
}

struct Energy{
    int value = 0;
};

struct Dimension{
    float width = 0.f;
    float length = 0.f;
    Dimension(float x = 0.f, float y = 0.f){
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
    DownDir = 1,
    LeftDir = 2,
    RightDir = 3
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
    const static ColorRGB WallColor(50, 50, 50);
    const static ColorRGB EmptyColor(152,223,138);
    const static ColorRGB CoinColor(188,189,34);
    const static ColorRGB BorderColor(112,50,21);
}
    
    
}//namespace pacman

#endif /* CommonIncludes_h */
