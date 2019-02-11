#ifndef __SYNTHETIC_SCENE_H__
#define __SYNTHETIC_SCENE_H__

#include "SceneData.h"

class SyntheticScene :
public SceneData,
public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    SCENE_CREATE_FUNC(SyntheticScene, "synthetic/SyntheticScene.csb")
    bool onCreate() override;
};

#endif // __SYNTHETIC_SCENE_H__
