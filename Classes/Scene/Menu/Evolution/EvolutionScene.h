#ifndef __EVOLUTION_SCENE_H__
#define __EVOLUTION_SCENE_H__

#include "SceneData.h"

class EvolutionScene :
public SceneData,
public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    SCENE_CREATE_FUNC(EvolutionScene, "evolution/EvolutionScene.csb")
    bool onCreate() override;
};

#endif // __EVOLUTION_SCENE_H__
