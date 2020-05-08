//
//  ScoreCard.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 08/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef ScoreCard_hpp
#define ScoreCard_hpp

#include "AllInterfaces.h"
#include "Settings.hpp"
#include "BlockingQueue.h"
#include "GameState.hpp"

namespace pacman { namespace impl{
    
    class ScoreCard: public IRenderered, public IPrimaryObject{
        GameState* gst =        nullptr;
        sf::Text                mRect;
        sf::Font                mfont;
        Position                position;
        Dimension               dimension;
        std::string             mText;
        
    public:
        void setGameState(GameState* st){
            gst = st;
        }
        virtual bool canBeRendered() override;
        virtual const ShapeList* getShapes()override;
        virtual DrawableObject* getShape()override;
        virtual void renderComplete()override;
        virtual void setPosition(const Position& p)override;
        virtual Position getPosition() override;
        
        virtual void create()override;
        virtual void destroy()override;
    };
    
}}

#endif /* ScoreCard_hpp */
