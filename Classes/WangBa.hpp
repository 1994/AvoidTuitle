//
//  WangBa.hpp
//  seven
//
//  Created by rimi on 15/6/12.
//
//

#ifndef WangBa_cpp
#define WangBa_cpp

#include <stdio.h>

#include "cocos2d.h"
USING_NS_CC;

class WangBa:public Sprite {
public:
    Sprite * createWangBa();
    
    static WangBa * getInstance();
    
    void BezierMove(Sprite* wangba,float duration,Vec2 destination,Vec2 control1,Vec2 control2);
    
private:
    static WangBa * m_wangba;
};

#endif /* WangBa_cpp */
