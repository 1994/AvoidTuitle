//
//  Music.cpp
//  seven
//
//  Created by rimi on 15/6/14.
//
//

#include "Music.hpp"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

void Music::playBGM(){
    SimpleAudioEngine::getInstance()->playBackgroundMusic("music/bg-music.mp3");
}

void Music::end(){
    SimpleAudioEngine::getInstance()->end();
}

void Music::playBoom(){
    SimpleAudioEngine::getInstance()->playEffect("music/boom.wav");
}

void Music::start(){
    SimpleAudioEngine::getInstance()->playEffect("music/start.wav");
}

void Music::bobble(){
    SimpleAudioEngine::getInstance()->playEffect("music/bobble.mp3");
}