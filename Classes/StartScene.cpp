//
//  StartScene.cpp
//  seven
//
//  Created by rimi on 15/6/14.
//
//

#include "StartScene.hpp"
#include "GameScene.h"
#include "Music.hpp"
Scene* StartScene::createScene()
{
   // this->setScore(score);
    auto scene = Scene::create();
    auto layer = StartScene::create();
    scene->addChild(layer);
    return scene;
}

bool StartScene::init(){
    if(!Layer::init())
        return false;
    
    this->setUI();
    Music::bobble();
    
    auto _emitter=ParticleSystemQuad::create("sea-pao01.plist");
    // auto _emitter1=ParticleSystemQuad::create("res/yezhi.plist");
    
    
    //_emitter->setDuration(10);
    _emitter->setStartSize(18.0);
    _emitter->setEndSize(29.0);
    //     设置例子纹理
    //
    auto texture=Director::getInstance()->getTextureCache()->addImage("res/shuidi.png");
    
    
    _emitter->setTexture(texture);
    _emitter->setPosition(Vec2(visibleSize.width/2,visibleSize.height/3));
    this->addChild(_emitter,200);

    
    return true;
}

void StartScene::setUI(){
    auto bg = Sprite::create("start.png");
    bg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(bg);
    
    auto startMenu = MenuItemImage::create("res/menu.png", "res/menu-close.png",[&](Ref * pSender){
        Music::start();
        auto scene = GameScene::createScene();
        auto fate = TransitionFade::create(0.2, scene, Color3B(0,0,0));
        Director::getInstance()->replaceScene(fate);
    });
    startMenu->setScaleY(1334/750+0.08);
    startMenu->setPosition(Vec2(visibleSize.width/2,visibleSize.height/3));
    auto menu = Menu::create(startMenu,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu,1);
    
    auto wuzei = Sprite::create("res/shuimu-menu.png");
    wuzei->setPosition(Vec2(startMenu->getPosition().x+startMenu->getContentSize().width/2-25,startMenu->getPosition().y-50));

    this->addChild(wuzei,4);
}
