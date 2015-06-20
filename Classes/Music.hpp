//
//  Music.hpp
//  seven
//
//  Created by rimi on 15/6/14.
//
//

#ifndef Music_cpp
#define Music_cpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class Music{
public:
    static void playBGM();
    
    static void end();
    
    static void playBoom();
    
    static void start();
    
    static void bobble();
};
#endif /* Music_cpp */
