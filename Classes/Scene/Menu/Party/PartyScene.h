//
//  PartyScene.h
//  PuzzleRPG
//
//  Created by neko on 2019/02/02.
//

#ifndef __PARTY_SCENE_H__
#define __PARTY_SCENE_H__

#include "SceneData.h"

class PartyScene :
public SceneData,
public cocos2d::Layer
{
public:
    PartyScene();
    static cocos2d::Scene* createScene();
    
    SCENE_CREATE_FUNC(PartyScene, "party/PartyScene.csb")
    bool onCreate() override;
    
    //シングルタップイベント
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event) override;
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event) override;
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event) override;
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event) override;
    
protected:
    void onRight();
    void onLeft();
    void onShowStatus(int id);
    void updateStorage();
    
    bool m_touchable; //タップの可否
};

#endif // __PARTY_SCENE_H__
