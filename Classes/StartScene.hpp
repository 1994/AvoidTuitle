//
//  StartScene.hpp
//  seven
//
//  Created by rimi on 15/6/14.
//
//

#ifndef StartScene_cpp
#define StartScene_cpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class StartScene : public cocos2d::Layer{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(StartScene);
private:
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    void setUI();
};
#endif /* StartScene_cpp */
