#ifndef __MYPAGE_SCENE_H__
#define __MYPAGE_SCENE_H__

#include "SceneData.h"

class MypageScene :
public SceneData,
public cocos2d::Layer
{
public:
    enum transition
    {
        transition_title = 0,
        transition_menu,
        transition_quest,
    };
    static transition m_transitionScene;
    
    MypageScene(); //コンストラクタ
    static cocos2d::Scene* createScene(transition scene);
    
    SCENE_CREATE_FUNC(MypageScene, "mypage/MypageScene.csb")
    bool onCreate() override;
};

#endif // __MYPAGE_SCENE_H__
