//
//  AnimationUtility.cpp
//  PuzzleRPG
//
//  Created by neko on 2019/03/21.
//

#include "AnimationUtility.h"
#include <string>

using namespace cocos2d;

void AnimationUtility::addAnimation(std::string fileName, float animationInterval, bool loop){
    
    Animation* animation = Animation::create();
    
    // ファイル名の連番は必ず０からにしておくこと
    int i = 0;
    while(true){
        std::string tt_str = "%02i.png";
        auto t_str = __String::createWithFormat(tt_str.c_str(),i);
        std::string str = fileName + "_" + t_str->getCString();
        
        SpriteFrame* sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(str.c_str());
        if(sprite == nullptr){
            break;
        }
        
        animation->addSpriteFrame(sprite);
        
        i++;
    }
    
    // アニメーションの間隔
    animation->setDelayPerUnit(animationInterval);
    
    // アニメーション終了後に最初に戻すかどうか
    animation->setRestoreOriginalFrame(loop);
    
    // キーの登録
    AnimationCache::getInstance()->addAnimation(animation, fileName);
}


Animation* AnimationUtility::getAnimation(std::string key){
    // アニメーションの取得
    return AnimationCache::getInstance()->getAnimation(key);
}
