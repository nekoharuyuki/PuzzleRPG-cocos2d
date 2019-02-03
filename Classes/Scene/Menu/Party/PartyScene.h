//
//  PartyScene.h
//  PuzzleRPG
//
//  Created by neko on 2019/02/02.
//

#ifndef __PARTY_SCENE_H__
#define __PARTY_SCENE_H__

#include "cocos2d.h"
#include "SceneData.h"

class PartyScene :
public SceneData,
public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    SCENE_CREATE_FUNC(PartyScene, "party/PartyScene.csb")
    bool onCreate() override;
};

#endif // __PARTY_SCENE_H__
