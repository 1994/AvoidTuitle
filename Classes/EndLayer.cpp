//
//  EndLayer.cpp
//  seven
//
//  Created by rimi on 15/6/15.
//
//

#include "EndLayer.hpp"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
using namespace cocos2d::network;
using namespace ui;
using namespace std;

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

int EndLayer::m_score = 0;

Scene* EndLayer::createScene(int score)
{
    m_score = score;
    auto scene = Scene::create();
    
    auto layer = EndLayer::create();
    scene->addChild(layer);
   
    log("score = %d",score);
    log("m_score = %d",m_score);
    return scene;
}


bool EndLayer::init()
{
    if(!Layer::init())
        return false;
    this->setUI();
    return true;
}

void EndLayer::setUI(){
    auto bg = Sprite::create("bg-3.png");
    bg->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(bg);
    
    auto gameover = Sprite::create("res/gameover.png");
    
    gameover->setPosition(visibleSize.width/2,visibleSize.height*3/4);
    
    this->addChild(gameover);
    
    std::string scoreText = "Your Score:";
    scoreText.append(patch::to_string(m_score));
    auto labelScore = Label::createWithTTF(scoreText, "fonts/Schwarzwald.ttf", 50);
    
    labelScore->setPosition(visibleSize.width/2,visibleSize.height*2/3);
    
    this->addChild(labelScore);
    
    auto restart = Button::create("res/restart.png");
    
    restart->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    
    restart->addClickEventListener([&](Ref * pSender){
        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(scene);
    });
    
    this->addChild(restart);
    
//    const char * postURL = "http://localhost:8080/API/query";
//    char data[100] = {0};
//    sprintf(data, "score=%d", m_score);
//    log(data);
//    HttpRequest* request = new HttpRequest();
//    request->setRequestType(HttpRequest::Type::POST);
//    request->setUrl(postURL);
//    request->setResponseCallback([&](cocos2d::network::HttpClient *sender, HttpResponse *response){
//
//        std::vector<char> *data = response->getResponseData();
//        std::string res;
//        for (int i = 0; i<data->size(); ++i) {
//            res += (*data)[i];
//        }
//        this->score = res;
//        log(strdup(res.c_str()));
//        auto label = Label::createWithSystemFont(score, "", 70);
//        label->setPosition(Vec2(200, 200));
//        label->setColor(Color3B(0, 0, 0));
//        this->addChild(label);
//    });
//    request->setRequestData(data,strlen(data));
//    HttpClient::getInstance()->send(request);
//    request->release();

}

