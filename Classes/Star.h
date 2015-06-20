//
//  Star.h
//  seven
//
//  Created by rimi on 15/6/10.
//
//

#ifndef __seven__Star__
#define __seven__Star__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

//星星
class Star:public Sprite{
public:
    static Sprite * createStar(int type);
};
#endif /* defined(__seven__Star__) */
