#ifndef __RESULT_SCENE_H__
#define __RESULT_SCENE_H__

#include "SceneData.h"

class ResultScene :
public SceneData,
public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(int quest_no);
    
    SCENE_CREATE_FUNC(ResultScene, "result/ResultScene.csb")
    bool onCreate() override;
    
private:
    int m_questNo;
};

#endif // __RESULT_SCENE_H__
