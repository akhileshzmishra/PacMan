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
    Dimension dim;
    Position loc;
    IBaseFramePtr baseFrame;
    IBluePrintPtr blueprint;
};

enum SettingsObservation{
    MainWindowDimensionChange,
    BoardDimensionChange,
    SquareDimensionChange,
    CoinDimensionChange,
    NoChange
};
    
typedef IObserver2<LiftData, SettingsObservation>      SettingObserver;
typedef ISubject2<LiftData, SettingsObservation>       SettingSubject;
    
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
    Position  mTopLeft;
    
    IBluePrintPtr mBluePrint;
    IBaseFramePtr mBaseFrame;
    
public:
    static Settings* getInstance();
    void start();
    
    const Dimension& getCoinDimension();
    const Dimension& getSquareDimension();
    const Dimension& getBoardDimension();
    const Position& getTopLeftMapPosition();
    const Dimension& getBoardBorders();
    const Dimension& getWindowDimension();
    
    ColorRGB getBoardColor();
    ColorRGB getEmptyColor();
    ColorRGB getWallColor();
    ColorRGB getCoinColor();
    
    GENERIC_GETTER_SETTER(BluePrint, mBluePrint, IBluePrintPtr);
    GENERIC_GETTER_SETTER(BaseFrame, mBaseFrame, IBaseFramePtr);
    
    void setWindowDimension(const Dimension& d);
    
    Position getPositionFromCoordinates(Coordinates c);
    
    void calculate();
 };
    
}}

#endif /* Settings_hpp */
