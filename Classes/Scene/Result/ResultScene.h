//
//  ResultScene.h
//  PuzzleRPG
//
//  Created by neko on 2019/04/14.
//

#ifndef __RESULT_SCENE_H__
#define __RESULT_SCENE_H__

#include "SceneData.h"
#include <random>

class ResultScene :
public SceneData,
public cocos2d::Layer
{
public:
    ResultScene();
    static cocos2d::Scene* createScene(int quest_no);
    
    SCENE_CREATE_FUNC(ResultScene, "result/ResultScene.csb")
    bool onCreate() override;
    
private:
    void setingDropCoin(Node* node);
    void setingDropChar(Node* node);
    
    static int m_questNo;                   // クエストの情報取得
};

#endif // __RESULT_SCENE_H__
