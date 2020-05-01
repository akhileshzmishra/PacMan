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

namespace pacman {namespace impl{
    
class Settings;
DECLARE_SHARED(Settings)
class Settings{
    Settings();
    Settings(const Settings& ) = delete;
    Settings(Settings&& ) = delete;
    Settings& operator = (const Settings& ) = delete;
    Settings& operator = (Settings&&) = delete;
    
public:
    static Settings* getInstance();
    Dimension getCoinDimension();
    Dimension getSquareDimension();
    Dimension getBoardDimension();
    Position getTopLeftMapPosition();
    Dimension getBoardBorders();
    Dimension getWindowDimension();
    
    ColorRGB getBoardColor();
    ColorRGB getEmptyColor();
    ColorRGB getWallColor();
    ColorRGB getCoinColor();
 };
    
}}

#endif /* Settings_hpp */
