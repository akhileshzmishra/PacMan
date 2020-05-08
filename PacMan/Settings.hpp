//
//  Settings.hpp
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef Settings_hpp
#define Settings_hpp

#include "CommonIncludes.h"
#include "AllInterfaces.h"



namespace pacman {namespace impl{

struct LiftData {
    
};

enum SettingsObservation{
    MainWindowDimensionChange,
    BoardDimensionChange,
    SquareDimensionChange,
    CoinDimensionChange,
    GameHasEnded,
    KeyPressedUp,
    KeyPressedDown,
    KeyPressedRight,
    KeyPressedLeft,
    NoChange
};
    
typedef IObserver2<LiftData, SettingsObservation>      SettingObserver;
typedef ISubject2<LiftData, SettingsObservation>       SettingSubject;
    
class SquarePositionData{
    Coordinates coordinates;
    Position    position;
public:
    GENERIC_GETTER_SETTER(Coordinates, coordinates, Coordinates)
    GENERIC_GETTER_SETTER(Position,    position,    Position)
};
    
typedef std::vector<SquarePositionData> SQRowPositionData;
typedef std::vector<SQRowPositionData>  SQMatrixData;
    
class Settings: public SettingSubject{
    Settings();
    Settings(const Settings& ) = delete;
    Settings(Settings&& ) = delete;
    Settings& operator = (const Settings& ) = delete;
    Settings& operator = (Settings&&) = delete;
    
    Dimension mSquareDimension;
    Dimension mWindowDimension;
    Dimension mBoardDimension;
    Dimension mBorders;
    Dimension mCoinDimension;
    Dimension mGhostDimension;
    Position  mTopLeft;
    
    IBluePrintPtr mBluePrint;
    IRendererPtr mRenderer;
    SQMatrixData mData;
    
    float    mPacManSpeed = 0.20;
    float    mGhostSpeed = 0.7;
    
    bool      coinAnimation = false;
    int       mTotalLives = 5;
    int       mTotalScore = 0;
public:
    static Settings* getInstance();
    void start();
    
    const Dimension& getCoinDimension();
    const Dimension& getSquareDimension();
    const Dimension& getBoardDimension();
    const Position& getTopLeftMapPosition();
    const Dimension& getBoardBorders();
    const Dimension& getWindowDimension();
    const Dimension& getGhostDimension(){
        return mGhostDimension;
    }
    
    ColorRGB getBoardColor();
    ColorRGB getEmptyColor();
    ColorRGB getWallColor();
    ColorRGB getCoinColor();
    
    GENERIC_GETTER_SETTER(BluePrint,       mBluePrint,      IBluePrintPtr);
    GENERIC_GETTER_SETTER(Renderer,        mRenderer,       IRendererPtr);
    GENERIC_GETTER_SETTER(coinAnimation,   coinAnimation,   bool);
    GENERIC_GETTER_SETTER(Lives,           mTotalLives,     int);
    GENERIC_GETTER_SETTER(Score,           mTotalScore,     int);
    
    void setWindowDimension(const Dimension& d);
    
    SquarePositionData* getSquarePositionData(const Coordinates& c);
    
    float getGhostSpeed(){
        return mGhostSpeed;
    }
    float getPacManSpeed(){
        return mPacManSpeed;
    }
    
    void calculate();
    
private:
    void refillSquarePositions();
 };
    
}}

#endif /* Settings_hpp */
