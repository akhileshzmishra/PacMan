//
//  Ghost.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef Ghost_hpp
#define Ghost_hpp

#include "AllInterfaces.h"
#include "GraphicIncludes.h"
#include "Settings.hpp"

namespace pacman {namespace impl{
    class Ghost: public IGhost, public SettingObserver,
    public std::enable_shared_from_this<IPlayer>{
    sf::CircleShape                 mHead;
    BoundingBox                     mBBox;
    int                             mSpeed = 1;
    bool                            mZombie = false;
    bool                            mDied = false;
    IBluePrintPtr                   mBluePrint;
    Coordinates                     mMazePos;
    size_t                          mRow;
    size_t                          mCol;
    Dimension                       SQuareDimension;
    Position                        mNextSquarePos;
    ISquareWeakPtr                  mHoldingSquare;
    IPlayBoardWeakPtr               mHoldingBoard;
    sf::RenderWindow*               mWin;
    float                           mRadius;
    bool                            mRenderable = true;
public:
    Ghost();
                
    virtual Dimension getDimension() override{
        return mBBox.dimension;
    }
    
    virtual void setPosition(const Position& p)override;
    virtual Position getPosition() override;
    virtual void create()override;
    virtual void destroy()override;
    virtual void setCurrentSquare(ISquarePtr)override;
    virtual ISquareWeakPtr getCurrentSquare()override;
    virtual void setBoard(IPlayBoardWeakPtr)override;
    virtual IPlayBoardWeakPtr getBoard()override;
    
    virtual void live()override;
    virtual bool isZombie()override;
    virtual void setZombie(bool s)override;
    virtual void died()override;
    
    virtual bool canBeRendered()override;
    virtual sf::Shape* getShape()override;
    void setRenderable(bool s) override{
        mRenderable = s;
    }
    virtual const std::vector<sf::Shape*>* getShapes() override{
        return nullptr;
    }

    virtual void renderComplete() override;
    void GetNotified(LiftData& data, const SettingsObservation& condition) override;
    
private:
    void createData();
};

DECLARE_SHARED(Ghost);

}}

#endif /* Ghost_hpp */
