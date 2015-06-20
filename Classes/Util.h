//
//  Util.h
//  seven
//
//  Created by rimi on 15/6/10.
//
//

#ifndef __seven__Util__
#define __seven__Util__
#include "cocos2d.h"
#include <stdio.h>
#include "string"
using namespace std;


class Util{
public:
    static int getRandomNumber(int start,int end){
        //srand((unsigned)time(0));
        return (arc4random() % end) + start;
      //  return CCRANDOM_0_1()*(end-start)+start;
    }
    
    
};

#endif /* defined(__seven__Util__) */
