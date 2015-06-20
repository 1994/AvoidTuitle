//
//  EndLayer.hpp
//  seven
//
//  Created by rimi on 15/6/15.
//
//

#ifndef EndLayer_cpp
#define EndLayer_cpp

#include <stdio.h>
#include "cocos2d.h"
#include "string"
USING_NS_CC;

class EndLayer : public Layer{
public:
    static cocos2d::Scene* createScene(int score);
    virtual bool init();
    CREATE_FUNC(EndLayer);
private:
    void setUI();
private:
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    static int m_score;
    
    std::string score;
};
#endif /* EndLayer_cpp */
