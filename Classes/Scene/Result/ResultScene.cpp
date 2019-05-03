//
//  ResultScene.cpp
//  PuzzleRPG
//
//  Created by neko on 2019/04/14.
//

#include "ResultScene.h"
#include "QuestScene.h"
#include "AudioManager.h"
#include "PlayerValue.h"
#include "PartyValue.h"
#include "MapData.h"
#include "BattleCharIconSprite.h"

USING_NS_CC;

using namespace cocostudio::timeline;

int ResultScene::m_questNo = 0;

ResultScene::ResultScene()
{
}

Scene* ResultScene::createScene(int quest_no)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ResultScene::create();
    
    m_questNo = quest_no;
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool ResultScene::onCreate()
{
    if ( !Layer::init() ){
        return false;
    }
    auto node = loaded();
    if(node == nullptr){
        return false;
    }
    
    // 勝利のBGM再生
    AudioManager::getInstance()->playBgm("victory");
    
    // ドロップ関連の設定
    setingDropCoin(node);
    setingDropChar(node);
    
    // メニューへ戻るボタン
    auto startBtn = node->getChildByName<ui::Button*>("QuestMap_btn");
    // タッチイベント追加
    startBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        
        // 0.5秒待ってからCallFuncを呼ぶ
        auto delay = DelayTime::create(0.5f);
        
        // クエストシーンへ移行する
        auto startGame = CallFunc::create([]{
            auto scene = QuestScene::createScene();
            AudioManager::getInstance()->playBgm("all_bgm");
            auto transition = TransitionFadeBL::create(0.5f, scene);
            Director::getInstance()->replaceScene(transition);
        });
        this->runAction(Sequence::create(delay, startGame, NULL));
    });
    
    this->scheduleUpdate();
    return true;
}

void ResultScene::setingDropCoin(Node* node)
{
    auto cointext = node->getChildByName<ui::Text*>("cointext");
    unsigned int dropCoin = MapData::getMapData(m_questNo).mapDropCoin;
    cointext->setString(std::to_string(dropCoin));
    
    // ユーザーデータ作成
    PlayerValue::getInstance()->dataLoad();
    unsigned int useCoin = PlayerValue::getInstance()->getCoin();
    useCoin += dropCoin;
    PlayerValue::getInstance()->setCoin(useCoin);
    PlayerValue::getInstance()->dataSave();
}

void ResultScene::setingDropChar(Node* node)
{
    std::vector<Node*> iconArray;
    iconArray.resize(5);
    int range = rand() % 5 + 1;
    auto partyValue = PartyValue::getInstance();
    if(partyValue){
        partyValue->dataLoad();
        for(int i = 0; i < 5; i++) {
            int charId = MapData::getMapData(m_questNo).mapDropChar[rand()% MapData::getMapData(m_questNo).mapDropChar.size()];
            iconArray[i] = node->getChildByName<Node*>("char"+std::to_string(i));
            if(iconArray[i]){
                auto charaPlayerSprite = BattleCharIconSprite::create(charId+1, BattleCharIconSprite::CharType::Member);
                if(charaPlayerSprite){
                    iconArray[i]->addChild( charaPlayerSprite );
                }
            }
            int storageId = partyValue->getMaxStorageId();
            partyValue->setCharStorageParam(storageId+1, charId, 5, 0);
            if(range == i+1){
                break;
            }
        }
        partyValue->dataSave();
    }
}
