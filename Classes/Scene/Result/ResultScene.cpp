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
#include "MapData.h"

USING_NS_CC;

using namespace cocostudio::timeline;

int ResultScene::m_questNo = 0;

ResultScene::ResultScene()
{
    std::random_device device;
    m_engine = std::default_random_engine(device());
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
    float rnd = (rand()/(RAND_MAX + 1.0f)) * 0.4f;
    unsigned int dropCoin = static_cast<unsigned int>((MapData::getMapData(m_questNo).mapDropCoin * (0.8f + rnd)));
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
    
}
