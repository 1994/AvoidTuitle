//
//  Actor.cpp
//  seven
//
//  Created by rimi on 15/6/9.
//
//

#include "Actor.h"

Actor * Actor::m_actor = nullptr;

Actor * Actor::getInstance(){
    if(m_actor==nullptr)
        m_actor = new Actor;
    return m_actor;
}

Sprite * Actor::getActor(){
    return Sprite::create();
}

Sprite * Actor::createActor()
{
    auto animation = Animation::create();
    
    auto actor = Sprite::create("res/1.png");
    
    for( int i=1;i<=6;i++)
    {
        char szName[100] = {0};
        sprintf(szName, "res/%d.png", i);
        animation->addSpriteFrameWithFile(szName);
    }
    // should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(2.8f / 20.0f);
    animation->setRestoreOriginalFrame(true);
    auto action = Animate::create(animation);
    actor->runAction(RepeatForever::create(action));
    return actor;
}
