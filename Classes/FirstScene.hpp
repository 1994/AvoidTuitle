//
//  FirstScene.hpp
//  seven
//
//  Created by rimi on 15/6/17.
//
//

#ifndef FirstScene_cpp
#define FirstScene_cpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class FirstScene : public Layer{
public:
    static Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(FirstScene);
    
private:
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
};
#endif /* FirstScene_cpp */
