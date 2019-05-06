//
//  PartyScene.h
//  PuzzleRPG
//
//  Created by neko on 2019/02/02.
//

#ifndef __PARTY_SCENE_H__
#define __PARTY_SCENE_H__

#include "SceneData.h"
#include "PartyValue.h"
#include "CharIconSprite.h"

class PartyScene :
public SceneData,
public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    SCENE_CREATE_FUNC(PartyScene, "party/PartyScene.csb")
    bool onCreate() override;
    
    //シングルタップイベント
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event) override;
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event) override;
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event) override;
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event) override;
    
private:
    PartyScene();
    ~PartyScene();
    
    void initParty(Node* node, PartyValue* partyValue);
    void initStorage(Node* node, PartyValue* partyValue);
    
    void onRight(Node* node);
    void onLeft(Node* node);
    void setStockIcon(Node* node);
    
    bool isTouchPartyIcon(cocos2d::Touch* touch);
    bool isTouchStorageIcon(cocos2d::Touch* touch);
    
    void updateParty();
    void updateStorage();
    
    void onShowStatus(int id);
    
    struct PartyListParams {
        int charId;
        int storageId;
        CharIconSprite* sprite;
    };
    std::map<int, PartyListParams> m_partyList;
    struct StockListParams {
        int charId;
        int storageId;
        CharIconSprite* sprite;
    };
    std::map<int, StockListParams> m_stockList;
    
    bool m_touchable;   //キャラアイコンのタップ可否
    int m_currentPos;
    int m_currentLimit;
};

#endif // __PARTY_SCENE_H__
