//
//  Bubble.h
//  seven
//
//  Created by rimi on 15/6/10.
//
//

#ifndef __seven__Bubble__
#define __seven__Bubble__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class Bubble:public Sprite{
public:
    static Sprite * createBubble();
    void setState(int state){this->m_state = state;};
    int getState(){return m_state;};
private:
    CREATE_FUNC(Bubble);
    
    //表示泡泡状态
    int m_state;
};
#endif /* defined(__seven__Bubble__) */
