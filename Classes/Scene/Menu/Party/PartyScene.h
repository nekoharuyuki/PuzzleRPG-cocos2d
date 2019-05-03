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
    
    void onShowStatus(int id);
    void updateStorage();
    
    struct PartyListParams {
        int charId;
        int storageId;
    };
    std::map<int, PartyListParams> m_partyList;
    struct StockListParams {
        int charId;
        int storageId;
    };
    std::map<int, StockListParams> m_stockList;
    
    bool m_touchable;   //キャラアイコンのタップ可否
    int m_currentPos;
    int m_currentLimit;
    
    int m_selectIcon;   // 選択中のキャラアイコンNo ( 1~8 : 1.2.3はパーティー / 0は選択していない　)
    
};

#endif // __PARTY_SCENE_H__
