//
//  IBluePrint.h
//  PacMan
//
//  Created by Akhilesh Mishra on 01/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IBluePrint_h
#define IBluePrint_h

namespace  pacman {
    class IBluePrint{
    public:
        virtual size_t getRow() = 0;
        virtual size_t getCol() = 0;
        
        virtual int getValue(size_t r, size_t c) = 0;
        virtual size_t getResolution() = 0;
    };
    
    DECLARE_SHARED(IBluePrint);
}
#endif /* IBluePrint_h */
