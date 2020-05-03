//
//  IThreadWork.h
//  PacMan
//
//  Created by Akhilesh Mishra on 02/05/20.
//  Copyright © 2020 Akhilesh Mishra. All rights reserved.
//

#ifndef IThreadWork_h
#define IThreadWork_h
#include "CommonIncludes.h"
namespace  pacman {
class IThreadWork{
public:
    virtual void work() = 0;
    virtual void setSpeed(float f) = 0;
};
    
DECLARE_SHARED(IThreadWork);

}

#endif /* IThreadWork_h */
