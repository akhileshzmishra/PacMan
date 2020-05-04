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
    ForeGround = 1,
    MaxLayer = 2
};
    
class IRenderer{
public:
    virtual void addRenderered(IRenderered* , RenderLayer layer) = 0;
    virtual void clearRendererd(IRenderered*) =  0;
    
};
    
class IRenderered{
public:
    virtual bool canBeRendered() = 0;
    virtual const ShapeList* getShapes() = 0;
    virtual sf::Shape* getShape() = 0;
    virtual void setRenderable(bool s) = 0;
    virtual void renderComplete() = 0;
};

}

#endif /* IBaseFrame_h */