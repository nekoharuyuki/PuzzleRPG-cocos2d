//
//  AnimationUtility.hpp
//  PuzzleRPG
//
//  Created by neko on 2019/03/21.
//

#ifndef AnimationUtility_hpp
#define AnimationUtility_hpp

class AnimationUtility
{
private:
    AnimationUtility();
    static AnimationUtility* m_animationUtility;
    
public:
    static AnimationUtility* getInstance();
    
    void addAnimation(std::string fileName, float animationInterval, bool loop = false);
    cocos2d::Animation* getAnimation(std::string key);
};

#endif /* AnimationUtility_hpp */
