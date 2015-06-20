//
//  GameScene.h
//  seven
//
//  Created by rimi on 15/6/10.
//
//

#ifndef __seven__GameScene__
#define __seven__GameScene__

#include <stdio.h>
#include "cocos2d.h"
#include "Actor.h"
USING_NS_CC;

//游戏主界面
class GameScene:public Layer {
public:
    static Scene * createScene();
    void  setPhysics(PhysicsWorld* world){this->m_physicsWorld = world;}
    
private:
    CREATE_FUNC(GameScene);
    virtual bool init();
    //添加物理边界
    void addEdge();
    
    //添加主角
    void addActor();
    
    //添加背景
    void addUI();
    
    void addStar(int i);
    
    void addShell();
    
    void addScore();
    
    void addWangBa();
    
    void addButton();
    
    void addDici();
    
    void addLizi();
    
    void addBoom(int i,int time);
    
    void addFish();
private:
    
    PhysicsWorld * m_physicsWorld;
    
    //我们的主角
    Sprite * m_actor =Actor::getInstance()->createActor();
    
    //分数
    Label * m_score = Label::createWithTTF("0", "fonts/Schwarzwald.ttf", 120);
    
    void update(float delta);
    
    void onExit();
    
private:
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    int flag;
    
    int temp;
    
    int number;
    
    int time =0;
    
    int score;
};
#endif /* defined(__seven__GameScene__) */
