//
//  Shell.cpp
//  seven
//
//  Created by rimi on 15/6/11.
//
//

#include "Shell.hpp"

Sprite * Shell::createShell(){
    
    auto shellBg  = Sprite::create("res/shell/shell-bg.png");
    auto panel = Sprite::create("res/shell/panel.png");
    
    auto shellUp = Sprite::create("res/shell/shell1-up.png");
    auto shellDown = Sprite::create("res/shell/shell-d.png");
    
    Size size = shellBg->getContentSize();
    
    auto animationOne = Animation::create();
    for( int i=1;i<=6;i++)
    {
        char szName[100] = {0};
        sprintf(szName, "res/shell/shell%d-up.png", i);
        animationOne->addSpriteFrameWithFile(szName);
    }
    // should last 2.8 seconds. And there are 14 frames.
    animationOne->setDelayPerUnit(0.2);
  //  animationOne->setRestoreOriginalFrame(true);
    
    auto animationTwo = Animation::create();
    
    for(int i=7;i<=11;i++){
        char szName[100] = {0};
        sprintf(szName, "res/shell/shell%d-up.png", i);
        animationTwo->addSpriteFrameWithFile(szName);
    }
    
    
    animationTwo->setDelayPerUnit(0.2);
  //  animationTwo->setRestoreOriginalFrame(true);
    
    auto actionOne = Animate::create(animationOne);
    
    auto actionTwo = Animate::create(animationTwo);
    
    
    shellUp->runAction(RepeatForever::create(Sequence::create(actionOne,DelayTime::create(2),actionTwo,DelayTime::create(2),NULL)));
    
    panel->setPosition(Vec2(size.width/2,size.height/2));
    shellUp->setPosition(Vec2(size.width/2,size.height/2));
    shellDown->setPosition(Vec2(size.width/2,size.height/2));
    panel->setScale(0.65);
    shellBg->addChild(shellUp,2);
    shellBg->addChild(shellDown,1);
    shellBg->addChild(panel,1);
    
    
    return shellBg;

}