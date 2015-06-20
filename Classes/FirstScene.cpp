//
//  FirstScene.cpp
//  seven
//
//  Created by rimi on 15/6/17.
//
//

#include "FirstScene.hpp"
#include "StartScene.hpp"
Scene* FirstScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    auto layer = FirstScene::create();
    scene->addChild(layer);
    return scene;
}


bool FirstScene::init()
{
    
    if ( !Layer::init())
    {
        return false;
    }
    auto bg = Sprite::create("first.png");
    bg->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(bg);
    
    auto _ClickListener = EventListenerTouchOneByOne::create();
    _ClickListener->onTouchBegan = [=](Touch *touch,Event *event)->bool{
        auto scene = StartScene::createScene();
        Director::getInstance()->replaceScene(scene);
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_ClickListener, this);
    return true;
}
