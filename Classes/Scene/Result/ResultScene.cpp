#include "ResultScene.h"
#include "QuestScene.h"
#include "AudioManager.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* ResultScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ResultScene::create();
    
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
