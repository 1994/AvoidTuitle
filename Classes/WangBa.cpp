//
//  WangBa.cpp
//  seven
//
//  Created by rimi on 15/6/12.
//
//

#include "WangBa.hpp"
WangBa * WangBa::m_wangba = nullptr;

WangBa * WangBa::getInstance(){
    if(m_wangba==nullptr)
        m_wangba = new WangBa;
    return m_wangba;
}

Sprite * WangBa::createWangBa(){
    auto wangba = Sprite::create("res/wangba.png");
    
    auto animation = Animation::create();
    
    for( int i=1;i<=4;i++)
    {
        char szName[100] = {0};
        sprintf(szName, "res/wangba/wugui0%d.png", i);
        animation->addSpriteFrameWithFile(szName);
    }

    animation->setDelayPerUnit(0.2);
   // animation->setRestoreOriginalFrame(true);
    
    auto action = Animate::create(animation);
    wangba->runAction(RepeatForever::create(action));


    wangba->setScale(0.6);
    return wangba;
}

void WangBa::BezierMove(Sprite * wangba,float duration,Vec2 destination,Vec2 control1,Vec2 control2){
    ccBezierConfig config;
    config.endPosition = destination;
    config.controlPoint_1=control1;
    config.controlPoint_2=control2;
    auto bezier = BezierTo::create(duration, config);
    wangba->runAction(bezier);
    
}