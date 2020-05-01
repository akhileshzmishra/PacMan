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

#define GENERIC_GETTER(fnname, variable, type) \
const type& getConstRef##fnname() { \
    return variable; \
} \
type& getRef##fnname() { \
    return variable; \
}

#define GENERIC_SETTER(fnname, variable, type) \
void set##fnname(const type& t) { \
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
typedef std::shared_ptr<className> className##Ptr;

namespace pacman{
    
typedef std::vector<int>                   VectorInt;
typedef std::vector<VectorInt>             VecVecInt;

typedef std::vector<bool>                  VectorBool;
typedef std::vector<VectorBool>            VecVecBool;

struct Coordinates{
    int x = 0;
    int y = 0;
};

struct Position{
    float x = 0.0f;
    float y = 0.0f;
    Position(float xa = 0.f, float ya = 0.f){
        x = xa;
        y = ya;
    }
};

namespace  mapElements {
    const int Empty                     = 0;
    const int Wall                      = 1;
    const int Invalid                   = 2;
    
    const int StartPos                  = 5;
    const int EnemyPos                  = 6;
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

struct DimensionMarker{
    Dimension dimension;
    Position  centroid;
};

enum class Directions{
    Up,
    Down,
    Left,
    Right
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
    const static ColorRGB WallColor(0, 0, 0);
    const static ColorRGB EmptyColor(152,223,138);
    const static ColorRGB CoinColor(188,189,34);
}
    
    
}//namespace pacman

#endif /* CommonIncludes_h */
