//
//  GameScene.cpp
//  seven
//
//  Created by rimi on 15/6/10.
//
//

#include "GameScene.h"
#include "Star.h"
#include "Bubble.h"
#include "Shell.hpp"
#include "iostream"
#include "WangBa.hpp"
#include "Util.h"
#include "ui/CocosGUI.h"
#include "Dici.hpp"
#include "Music.hpp"
#include "Boom.hpp"
#include "EndLayer.hpp"
#include "Fish.hpp"
#include "string"

using namespace ui;
using namespace std;
//2015-6-19 add

#include <sstream>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

#define UPTAG 100
#define LEFTANDRIGHTTAG 200
#define ACTORTAG 50
#define STARTAG 60
#define WANGBATAG 300
#define DICITAG 400
#define BOOMTAG 550
#define FISHTAG 600
Scene * GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = GameScene::create();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    //设置重力环境
    scene->getPhysicsWorld()->setGravity(Vec2(0,-1500));
    
    layer->setPhysics(scene->getPhysicsWorld());
    scene->addChild(layer);
    
    return scene;
}
bool GameScene::init()
{
    if(!Layer::init())
        return false;
    
    auto _emitter=ParticleSystemQuad::create("sea-pao01.plist");
    
    _emitter->setEndColor(Color4F(0,0,0,1));
    _emitter->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    
    this->addChild(_emitter,200);

    
  //  this->addLizi();
    
    this->addEdge();
    
    this->addUI();
    
    this->addActor();
    
    this->addShell();
    
    this->addScore();

    
   // this->addButton();
    
    this->addDici();
    
    Music::playBGM();
    
    this->scheduleUpdate();
    
    return true;
}

void GameScene::addEdge()
{
   
    auto bodyBox = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    
    auto edgeBox = Node::create();
    edgeBox->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    edgeBox->setPhysicsBody(bodyBox);
    
    this->addChild(edgeBox);
    
    
    auto bodyUp = PhysicsBody::createEdgeBox(Size(visibleSize.width,2));
    bodyUp->setCategoryBitmask(0xFFFFFFFF);
    bodyUp->setContactTestBitmask(0xFFFFFFFF);
    auto edgeUp = Node::create();
    edgeUp->setTag(UPTAG);
    edgeUp->setPosition(Vec2(visibleSize.width/2,visibleSize.height));
    edgeUp->setPhysicsBody(bodyUp);
    this->addChild(edgeUp,1);

    
    // auto bodyDown = PhysicsBody::createEdgeBox(Size(visibleSize.width,2));
    // bodyDown->setCategoryBitmask(0xFFFFFFFF);
    // bodyDown->setContactTestBitmask(0xFFFFFFFF);

    // auto edgeDown = Node::create();
    // edgeDown->setPosition(Vec2(visibleSize.width/2,0));
    // edgeDown->setPhysicsBody(bodyDown);
    // edgeDown->setTag(2);
    // this->addChild(edgeDown,1);
    
    
    auto bodyLeft = PhysicsBody::createEdgeBox(Size(3,visibleSize.height));
    bodyLeft->setCategoryBitmask(0xFFFFFFFF);
    bodyLeft->setContactTestBitmask(0xFFFFFFFF);
    bodyLeft->getFirstShape()->setRestitution(1);
    
    auto edgeLeft = Node::create();
    edgeLeft->setPosition(Vec2(0,visibleSize.height/2));
    edgeLeft->setTag(LEFTANDRIGHTTAG);
    edgeLeft->setPhysicsBody(bodyLeft);
    this->addChild(edgeLeft,1);
    
    auto bodyRight = PhysicsBody::createEdgeBox(Size(3,visibleSize.height));
    bodyRight->setCategoryBitmask(0xFFFFFFFF);
    bodyRight->setContactTestBitmask(0xFFFFFFFF);
    bodyRight->getFirstShape()->setRestitution(1);
    
    auto edgeRight = Node::create();
    edgeRight->setPosition(Vec2(visibleSize.width,visibleSize.height/2));
    edgeRight->setTag(LEFTANDRIGHTTAG);
    edgeRight->setPhysicsBody(bodyRight);
    this->addChild(edgeRight,1);
    
    
    auto body = PhysicsBody::createBox(m_actor->getContentSize());
    body->setContactTestBitmask(0xFFFFFFFF);
    body->setEnable(true);
    body->setGravityEnable(true);
    body->setDynamic(true);
    body->setRotationEnable(false);
    body->setVelocity(Vec2(-800,0));
  //  log("mass  = %f",body->getMass());
    
    //body->setVelocityLimit(1200.0f);
    body->applyForce(Vec2(-10000,0));
    body->getFirstShape()->setRestitution(1);
    
  //  log("mess = %f",body->getMass());
    
    m_actor->setPhysicsBody(body);
    m_actor->getPhysicsBody()->setMass(500.0f);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [this](PhysicsContact& contact)->bool
    {
      //  log("up");
        
        auto SpriteA = (Sprite *)contact.getShapeA()->getBody()->getNode();
        auto SpriteB = (Sprite *)contact.getShapeB()->getBody()->getNode();
        
        if(SpriteA&&SpriteB){
            
            log("A TAG = %d",SpriteA->getTag());
            
            log("B TAG = %d",SpriteB->getTag());
            
            if(SpriteA&&SpriteB&&SpriteA->getTag()==UPTAG&&SpriteB->getTag()==ACTORTAG)
            {
                //log("actor 撞 上面");
                return true;
            }
            
            if(SpriteA&&SpriteB&&SpriteA->getTag()==STARTAG&&SpriteB->getTag()==UPTAG)
            {
               // log("star 撞上面");
                this->removeChild(SpriteA);
                return true;
            }
            
            if(SpriteA&&SpriteB&&SpriteA->getTag()==LEFTANDRIGHTTAG&&SpriteB->getTag()==ACTORTAG)
            {
                Vec2 currentSpeed = SpriteB->getPhysicsBody()->getVelocity();
               // log("speed.x = %f,speed.y= %f",currentSpeed.x,currentSpeed.y);
                if(currentSpeed.x<0){
                    SpriteB->getPhysicsBody()->resetForces();
                    SpriteB->getPhysicsBody()->applyForce(Vec2(10000.0f,0));
                    SpriteB->getPhysicsBody()->setVelocity(Vec2(800,currentSpeed.y));

                }else {
                    SpriteB->getPhysicsBody()->resetForces();
                    SpriteB->getPhysicsBody()->applyForce(Vec2(-10000.0f,0));
                    SpriteB->getPhysicsBody()->setVelocity(Vec2(-800,currentSpeed.y));
                }
                return true;
            }
            
            if(SpriteA&&SpriteB&&SpriteA->getTag()==STARTAG&&SpriteB->getTag()==STARTAG)
            {
            //    log("paopao撞到了");
                return true;
            }
            
            if(SpriteA&&SpriteB&&SpriteA->getTag()==STARTAG&&SpriteB->getTag()==ACTORTAG)
            {
                this->removeChild(SpriteA);
                score++;
                return true;
            }
            
            if(SpriteA&&SpriteB&&SpriteA->getTag()==WANGBATAG&&SpriteB->getTag()==ACTORTAG)
            {
                Vec2 speed = SpriteB->getPhysicsBody()->getVelocity();
                if(speed.x>0)
                    SpriteB->getPhysicsBody()->setVelocity(Vec2(speed.x+400,speed.y));
                else
                    SpriteB->getPhysicsBody()->setVelocity(Vec2(speed.x-400,speed.y));
                return true;
            }
            
            if(SpriteA&&SpriteB&&SpriteA->getTag()==DICITAG&&SpriteB->getTag()==ACTORTAG)
            {
                auto end = EndLayer::createScene(score);
                Director::getInstance()->replaceScene(end);
                return true;
            }
            
            //boom
            if(SpriteA&&SpriteB&&SpriteA->getTag()==BOOMTAG&&SpriteB->getTag()==ACTORTAG)
            {
                Music::playBoom();
                auto _emitter=ParticleSystemQuad::create("baozha01.plist");
      
        
                _emitter->setDuration(0.2);
                _emitter->setStartSize(18.0);
                _emitter->setEndSize(29.0);
                //     设置例子纹理
                //
                auto texture=Director::getInstance()->getTextureCache()->addImage("boom-shape.png");
                
                _emitter->setTexture(texture);
                
                _emitter->setPosition(SpriteA->getPosition());
                
                _emitter->setEndColor(Color4F(0,0,0,0));
                
                this->addChild(_emitter,4);
                
                this->removeChild(SpriteA);
                
                _eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
                
                SpriteB->setColor(Color3B(0,0,0));
                
                //失去知觉
                
                
                return true;
            }
            
            
            if(SpriteA&&SpriteB&&SpriteA->getTag()==BOOMTAG&&SpriteB->getTag()==DICITAG)
            {
                auto _emitter=ParticleSystemQuad::create("baozha01.plist");
                _emitter->setDuration(0.2);
                _emitter->setStartSize(18.0);
                _emitter->setEndSize(29.0);
                auto texture=Director::getInstance()->getTextureCache()->addImage("boom-shape.png");
                _emitter->setTexture(texture);
                
                _emitter->setPosition(SpriteA->getPosition());
                
                _emitter->setEndColor(Color4F(0,0,0,0));
                
                this->addChild(_emitter,4);

                this->removeChild(SpriteA);
                
                return true;
            }
            if(SpriteA&&SpriteB&&SpriteA->getTag()==WANGBATAG&&SpriteB->getTag()==LEFTANDRIGHTTAG){
                this->removeChild(SpriteA);
            }
            if(SpriteA&&SpriteB&&SpriteA->getTag()==ACTORTAG&&SpriteB->getTag()==FISHTAG){
                score++;
                this->removeChild(SpriteB);
            }
            if(SpriteA&&SpriteB&&SpriteA->getTag()==FISHTAG&&SpriteB->getTag()==ACTORTAG){
                score=score+2;
                this->removeChild(SpriteA);
            }
        }
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    
}


void GameScene::addActor()
{
    m_actor->setScale(0.3);
    
    m_actor->setTag(ACTORTAG);
    
    m_actor->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y+400));
    
    this->addChild(m_actor,1);
    
    //添加事件监听
    auto _ClickListener = EventListenerTouchOneByOne::create();
    _ClickListener->onTouchBegan = [=](Touch *touch,Event *event)->bool{
        log("Click");

        Vec2 speed = m_actor->getPhysicsBody()->getVelocity();
        m_actor->getPhysicsBody()->setVelocity(Vec2(speed.x,speed.y+800));
        return true;
    };
    
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_ClickListener, this);
    
    
}

void GameScene::addUI()
{
    auto bg = Sprite::create("bg-3.png");
    bg->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(bg);
}

void GameScene::addStar(int i)
{
    int randType = Util::getRandomNumber(1, 9);

    log("随机数: %d",randType);
    auto star = Star::createStar(randType);
    
    auto bodyStar = PhysicsBody::createCircle(star->getContentSize().width/2);
    
    bodyStar->setCategoryBitmask(0xFFFFFFFF);
    bodyStar->setContactTestBitmask(0xFFFFFFFF);

    bodyStar->setDynamic(true);
    bodyStar->setMass(0.8);
    
    star->setPosition(Vec2(200*i,200));
    star->setPhysicsBody(bodyStar);
    star->setTag(STARTAG);
    star->getPhysicsBody()->setGravityEnable(false);
    
    this->addChild(star);
    
    int control1_x = Util::getRandomNumber(0, visibleSize.width);
    
    int control1_y = Util::getRandomNumber(0, visibleSize.height);
    
    int control2_x = Util::getRandomNumber(0, visibleSize.width);
    
    int control2_y = Util::getRandomNumber(0, visibleSize.height);
    
    int destina_x = Util::getRandomNumber(0, visibleSize.width);
    
    WangBa::getInstance()->BezierMove(star, 4, Vec2(destina_x,visibleSize.height), Vec2(control1_x,control1_y), Vec2(control2_x,control2_y));
    
}

void GameScene::update(float delta)
{

    //  srand((unsigned)time(0));
    time++;
   // log("time = %d",time);
    temp++;
    if(time>1000){
        if(temp%50==0){
            // srand((unsigned)time(NULL));
            number++;
            if(number>3){
                number = 0;
            }
            this->addStar(number);
            // this->addWangBa();
            int shaizi = Util::getRandomNumber(0, 4);
            if(shaizi==2){
                this->addWangBa();
            }
            
            if(shaizi==0)
                this->addFish();
            
            //if(shaizi==1)
                this->addBoom(Util::getRandomNumber(1, 8),time);
           
            temp = temp%50;
        }
    } else {
        if(temp%100==0){
            // srand((unsigned)time(NULL));
            number++;
            if(number>3){
                number = 0;
            }
            this->addStar(number);
            // this->addWangBa();
            int shaizi = Util::getRandomNumber(0, 4);
            if(shaizi==2){
                this->addWangBa();
            }
            if(shaizi==3)
                this->addFish();
            if(shaizi==4)
                this->addBoom(Util::getRandomNumber(1, 8),time);
            //this->addBoom(Util::getRandomNumber(1,8));
            temp = temp%100;
        }

    }
  
    
    //更新分数
    m_score->setTextColor(Color4B(0,0,0,50));
    
    m_score->setString(patch::to_string(score));
    
    Vec2 currentPosition = m_actor->getPosition();
    
    log("position.x = %f",currentPosition.x);
    
    if(currentPosition.x>visibleSize.width||currentPosition.x<0){
        auto end = EndLayer::createScene(score);
        Director::getInstance()->replaceScene(end);
    }
}

void GameScene::addShell(){
    auto shell = Shell::createShell();
    
//    auto bodyShell = PhysicsBody::createEdgeBox(shell->getContentSize());
    shell->setPosition(Vec2(200,100));
//    shell->setPhysicsBody(bodyShell);
    this->addChild(shell);
}

void GameScene::addScore(){
    m_score->setPosition(Vec2(visibleSize.width/2,900));
    this->addChild(m_score);
    
}

void GameScene::addWangBa(){
    
    auto wangba = WangBa::getInstance()->createWangBa();
    
    auto bodyWangBa = PhysicsBody::createEdgeBox(wangba->getContentSize()*0.6);
    
    bodyWangBa->setCategoryBitmask(0x0001);
    bodyWangBa->setContactTestBitmask(0x0001);
//    bodyWangBa->setCategoryBitmask(0xFFFFFFFF);
//    bodyWangBa->setContactTestBitmask(0xFFFFFFFF);
//    
    bodyWangBa->getFirstShape()->setRestitution(1.0F);
    
    wangba->setPosition(Vec2(0,Util::getRandomNumber(0, visibleSize.height)));
    
    wangba->setTag(WANGBATAG);
    
    wangba->setPhysicsBody(bodyWangBa);
    
    this->addChild(wangba);
    
    
    int control1_x = Util::getRandomNumber(0, visibleSize.width);
    
    int control1_y = Util::getRandomNumber(0, visibleSize.height);
    
    int control2_x = Util::getRandomNumber(0, visibleSize.width);
    
    int control2_y = Util::getRandomNumber(0, visibleSize.height);
    
    int destina_y = Util::getRandomNumber(0, visibleSize.height);
    
    WangBa::getInstance()->BezierMove(wangba, 4, Vec2(visibleSize.width+100,destina_y), Vec2(control1_x,control1_y), Vec2(control2_x,control2_y));
    
}

void GameScene::addButton(){
    auto btn = Button::create("CloseNormal.png");
    btn->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    
    this->addChild(btn);
    //[](){}const ccWidgetClickCallback &callback
    btn->addClickEventListener([&](Ref * pSender){
        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    });
}


void GameScene::addDici(){
    auto dici = Dici::createDici();
    auto bodyDici = PhysicsBody::createEdgeBox(dici->getContentSize());
    bodyDici->setCategoryBitmask(0xFFFFFFFF);
    bodyDici->setContactTestBitmask(0xFFFFFFFF);
    dici->setTag(DICITAG);
    dici->setAnchorPoint(Vec2(0.5,0));
    dici->setPosition(Vec2(visibleSize.width/2,22));
    dici->setPhysicsBody(bodyDici);
    this->addChild(dici);
}

void GameScene::onExit(){
    Layer::onExit();
    Music::end();
}

void GameScene::addLizi(){

    auto _emitter=ParticleSystemQuad::create("pao-gamesence.plist");

    _emitter->setStartSize(18.0);
    
    _emitter->setEndSize(29.0);
    
    _emitter->setEndColor(Color4F(0,0,0,1));
    _emitter->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    
    this->addChild(_emitter,200);

}

void GameScene::addBoom(int i,int time){
   
   // bodyBoom->getFirstShape()->setRestitution(1);
    
    auto boom = Boom::createBoom();
    boom->setTag(BOOMTAG);
    boom->setPosition(Vec2(100*i,visibleSize.height));
    float scale = 0.2;
    boom->setScale(scale);
    auto bodyBoom = PhysicsBody::createCircle(boom->getContentSize().width/2*scale);
    bodyBoom->setMass(4000.0f);
    bodyBoom->setCategoryBitmask(0x0001);
    bodyBoom->setContactTestBitmask(0x0001);
    if(time>1000){
        bodyBoom->applyForce(Vec2(0,-20000.0f));
        bodyBoom->setVelocity(Vec2(0,-200));
    }
    
    else {
        bodyBoom->applyForce(Vec2(0,-10000.0f));
        bodyBoom->setVelocity(Vec2(0,-100));
    }
    boom->setPhysicsBody(bodyBoom);
    
    this->addChild(boom,3);
}

void GameScene::addFish(){
    int number = Util::getRandomNumber(1, 3);
    
    for(int i=0;i<number;i++){
        int type = Util::getRandomNumber(2, 3);
        
        log("type = %d",type);
        if(type==4)
            return;
        auto fish = Fish::createFish(type);
        
        int position_y = Util::getRandomNumber(100, visibleSize.height-100);
        if(type==0||type==3){
            
            fish->setPosition(Vec2(0,position_y));
            
            int control1_x = Util::getRandomNumber(0, visibleSize.width);
            
            int control1_y = Util::getRandomNumber(0, visibleSize.height);
            
            int control2_x = Util::getRandomNumber(0, visibleSize.width);
            
            int control2_y = Util::getRandomNumber(0, visibleSize.height);
            
            int destina_y = Util::getRandomNumber(0, visibleSize.height);
            
            WangBa::getInstance()->BezierMove(fish, 4, Vec2(visibleSize.width+100,destina_y), Vec2(control1_x,control1_y), Vec2(control2_x,control2_y));
        }
        
        else{
            fish->setPosition(Vec2(visibleSize.width,position_y));
            
            int control1_x = Util::getRandomNumber(0, visibleSize.width);
            
            int control1_y = Util::getRandomNumber(0, visibleSize.height);
            
            int control2_x = Util::getRandomNumber(0, visibleSize.width);
            
            int control2_y = Util::getRandomNumber(0, visibleSize.height);
            
            int destina_y = Util::getRandomNumber(0, visibleSize.height);
            
            WangBa::getInstance()->BezierMove(fish, 4, Vec2(-300,destina_y), Vec2(control1_x,control1_y), Vec2(control2_x,control2_y));

        }
        this->addChild(fish);
        //this->addChild(fish);
    }
    
    
    
}