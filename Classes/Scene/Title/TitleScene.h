//
//  TitleScene.h
//  PuzzleRPG
//
//  Created by neko on 2019/02/03.
//

#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"
#include "SceneData.h"

class TestController;

class TitleScene :
public SceneData,
public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    SCENE_CREATE_FUNC(TitleScene, "title/TitleScene.csb")
    bool onCreate() override;
    
private:
    
    void titleSceneButtonPress(Node* rootNode);
    void startButtonPress(Node* rootNode);
    void mypageButtonPress(Node* rootNode);
    void otherButtonPress(Node* rootNode);
    void debugButtonPress(Node* rootNode);
    
    static cocos2d::Scene* m_scene;
    
#if COCOS2D_DEBUG
    TestController* m_projectController;
#endif
};

#endif // __TITLE_SCENE_H__
