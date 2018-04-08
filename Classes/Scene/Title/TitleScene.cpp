#include "TitleScene.h"
#include "CharselectScene.h"
#include "QuestScene.h"
#include "OtherScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "GameDataSQL.h"
#include "AudioManager.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* TitleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // タイトル画面へ移行する前の映像
    
    auto rootNode = CSLoader::createNode("title/TitleScene.csb");
    if(rootNode == nullptr){
        return false;
    }
    addChild(rootNode);
    
    // タイトルBGM再生
    AudioManager::getInstance()->playBgm("all_bgm");
    
    // スタートボタンが押された時の処理
    startButtonPress(rootNode);
    
    // その他のボタンが押された時の処理
    otherButtonPress(rootNode);
    
    this->scheduleUpdate();
    return true;
}

// スタートボタンが押された時の処理
void TitleScene::startButtonPress(Node* rootNode)
{
    // ボタンノードを取得
    auto startBtn = rootNode->getChildByName<ui::Button*>("start_btn");
    // タッチイベント追加
    startBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        
        // 0.5秒待ってからCallFuncを呼ぶ
        auto delay = DelayTime::create(0.2f);
        
        // ゲームを始めるアクション
        auto startGame = CallFunc::create([]{
            
            // スタートボタン音SE再生
            AudioManager::getInstance()->playSe("ui_title_start");
            
            // ローカルDBデータの有無を確認
            if(!GameDataSQL::hasData()){
                // キャラクター選択画面へ移行
                auto transition = TransitionFade::create(0.5f, CharselectScene::createScene(), Color3B::WHITE);
                Director::getInstance()->replaceScene(transition);
            } else {
                // クエスト選択画面へ移行
                auto transition = TransitionFade::create(0.5f, QuestScene::createScene(), Color3B::WHITE);
                Director::getInstance()->replaceScene(transition);
            }
        });
        this->runAction(Sequence::create(delay, startGame, NULL));
        return true;    // イベントを実行する
    });
}

// その他のボタンが押された時の処理
void TitleScene::otherButtonPress(Node* rootNode)
{
    // ボタンノードを取得
    auto startBtn = rootNode->getChildByName<ui::Button*>("ui_etc_btn");
    // タッチイベント追加
    startBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        
        // 0.5秒待ってからCallFuncを呼ぶ
        auto delay = DelayTime::create(0.2f);
        
        // ゲームを始めるアクション
        auto startGame = CallFunc::create([]{
            auto transition = TransitionFade::create(0.5f, OtherScene::createScene(OtherScene::transition_title), Color3B::WHITE);
            Director::getInstance()->replaceScene(transition);
        });
        this->runAction(Sequence::create(delay, startGame, NULL));
        return true;    // イベントを実行する
    });
}
