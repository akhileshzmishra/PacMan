//
//  ElementalSignal.h
//  ProcUtils
//
//  Created by Akhilesh Mishra on 31/07/19.
//  Copyright © 2019 Akhilesh Mishra. All rights reserved.
//

#ifndef ElementalSignal_h
#define ElementalSignal_h
#include "CommonIncludes.h"

template<class T, T setValue, T notSetValue>
class ElementalSignal{
    std::mutex _m;
    std::condition_variable _cv;
    T _elem;
public:
    ElementalSignal(){
        _elem = notSetValue;
    }
    
    void reset(){
        _elem = notSetValue;
    }
    
    void signal(){
        _elem = setValue;
        _cv.notify_one();
    }
    
    T value(){
        return _elem;
    }
    
    void wait(int timeInMillisec = -1) {
        std::unique_lock<std::mutex> lk(_m);
        if (timeInMillisec > 0) {
            _cv.wait_for(lk, std::chrono::milliseconds(timeInMillisec * 1000), [&]{
                return (_elem == setValue);
            });
        }
        else {
            _cv.wait(lk, [&]{
                return (_elem == setValue);
            });
        }
    }
};

typedef ElementalSignal<bool, true, false> BoolSignal;

#endif /* ElementalSignal_h */
