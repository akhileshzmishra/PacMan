//
//  IBaseFrame.h
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IBaseFrame_h
#define IBaseFrame_h
#include "CommonIncludes.h"
#include "GraphicIncludes.h"

namespace  pacman {
class IRenderered;
class IRenderer;
DECLARE_SHARED(IRenderer);
DECLARE_SHARED(IRenderered);
    
typedef std::vector<sf::Shape*> ShapeList;
enum RenderLayer{
    Background = 0,
    Middleground = 1,
    ForeGround = 2,
    MaxLayer = 3
};
    
struct RenderingJob{
    IRenderered* ptr = nullptr;
    Position   pos;
    float      speed = 0.2;
    bool       ifSpeed = false;
};

class IRenderer{
public:
    virtual ~IRenderer(){}
    virtual void addRenderered(IRenderered* , RenderLayer layer) = 0;
    virtual void clearRendererd(IRenderered*) =  0;
    virtual void addMovable(RenderingJob& j) = 0;
    
};
    
class IRenderered{
public:
    virtual ~IRenderered(){}
    virtual bool canBeRendered() = 0;
    virtual const ShapeList* getShapes() = 0;
    virtual sf::Shape* getShape() = 0;
    virtual void renderComplete() = 0;
};

}

#endif /* IBaseFrame_h */
