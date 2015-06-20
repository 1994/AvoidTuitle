//
//  Fish.cpp
//  seven
//
//  Created by rimi on 15/6/12.
//
//

#include "Fish.hpp"
#define FISHTAG 600
Sprite * Fish::createFish(int type){
    switch (type) {

        case 2:
        {
            auto animation = Animation::create();
            
            auto fish = Sprite::create("res/fish1-01.png");
            
            for( int i=1;i<=6;i++)
            {
                char szName[100] = {0};
                sprintf(szName, "res/fish1-0%d.png", i);
                animation->addSpriteFrameWithFile(szName);
            }
     
            animation->setDelayPerUnit(0.2);
        
            auto action = Animate::create(animation);
            
            fish->runAction(RepeatForever::create(action));
            
            auto bodyFish = PhysicsBody::createBox(fish->getContentSize());
            
            bodyFish->setCategoryBitmask(0x0010);
            
            bodyFish->setContactTestBitmask(0x0010);
            
            bodyFish->setGravityEnable(false);
            
            fish->setTag(FISHTAG);
            
            fish->setPhysicsBody(bodyFish);
            
            return fish;
            break;
        }

            
            //3 左边出的鱼
        case 3:
        {
            auto animation = Animation::create();
            
            auto fish = Sprite::create("res/fish-1.png");
            
            for( int i=1;i<=4;i++)
            {
                char szName[100] = {0};
                sprintf(szName, "res/fish-%d.png", i);
                animation->addSpriteFrameWithFile(szName);
            }

            animation->setDelayPerUnit(0.2);

            auto action = Animate::create(animation);
            
            fish->runAction(RepeatForever::create(action));
            
            //return actor;
            return fish;
            break;
        }
    
        default:
            return Sprite::create("res/fish01.png");
            break;
    }
}