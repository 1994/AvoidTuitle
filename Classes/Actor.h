//
//  Actor.h
//  seven
//
//  Created by rimi on 15/6/9.
//
//

#ifndef __seven__Actor__
#define __seven__Actor__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class Actor:public cocos2d::Sprite{
private:
    Actor(){};
    static Actor * m_actor;
public:
    
    static Actor * getInstance();
    
    Sprite * getActor();
    
    Sprite * createActor();
};
#endif /* defined(__seven__Actor__) */
