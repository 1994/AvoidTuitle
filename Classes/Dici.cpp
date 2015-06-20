//
//  Dici.cpp
//  seven
//
//  Created by rimi on 15/6/12.
//
//

#include "Dici.hpp"
Sprite * Dici::createDici(){
   // auto diciBatch = SpriteBatchNode::create("");
    auto dici = Sprite::create("res/dici1.png");
    return dici;
}