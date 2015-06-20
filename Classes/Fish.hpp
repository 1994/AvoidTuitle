//
//  Fish.hpp
//  seven
//
//  Created by rimi on 15/6/12.
//
//

#ifndef Fish_cpp
#define Fish_cpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class Fish:public Sprite {
public:
    static Sprite * createFish(int type);
};
#endif /* Fish_cpp */
