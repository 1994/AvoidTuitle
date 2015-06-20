//
//  Star.cpp
//  seven
//
//  Created by rimi on 15/6/10.
//
//

#include "Star.h"
//根据类型生成星星、珊瑚气泡
Sprite * Star::createStar(int type){
    
    switch (type) {
        case 1:
            return Sprite::create("res/start_pao01.png");
            break;
        case 2:
            return Sprite::create("res/start_pao02.png");
            break;
        case 3:
            return Sprite::create("res/start_pao03.png");
            break;
        case 4:
            return Sprite::create("res/start_pao04.png");
            break;
        case 5:
            return Sprite::create("res/start_pao05.png");
            break;
        case 6:
            return Sprite::create("res/shanhu01.png");
            break;
        case 7:
            return Sprite::create("res/shanhu02.png");
            break;
        case 8:
            return Sprite::create("res/shanhu03.png");
            break;
        case 9:
            return Sprite::create("res/shanhu04.png");
            break;
        default:
            return Sprite::create("res/start_pao01.png");
            break;
    }
    

}