//
//  TitleScene.cpp
//  PuzzleRPG
//
//  Created by neko on 2019/02/03.
//

#include "TitleScene.h"
#include "CharselectScene.h"
#include "QuestScene.h"
#include "MypageScene.h"
#include "OtherScene.h"
#include "PlayerValue.h"
#include "GameDataSQL.h"
#include "AudioManager.h"

#if COCOS2D_DEBUG
#include "Controller.h"
#include "tests.h"
#endif

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* TitleScene::m_scene = nullptr;

Scene* TitleScene::createScene()
{
    // 'scene' is an autorelease object
    m_scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = TitleScene::create();
    // add layer as a child to scene
    m_scene->addChild(layer);
    // return the scene
    return m_scene;
}

bool TitleScene::onCreate()
{
    if ( !Layer::init() ){
        return false;
    }
    auto node = loaded();
    if(node == nullptr){
        return false;
    }
    // タイトルBGM再生
    AudioManager::getInstance()->playBgm("all_bgm");
    // タイトル画面のボタン処理
    titleSceneButtonPress(node);
    this->scheduleUpdate();
    return true;
}

// タイトル画面のボタン処理
void TitleScene::titleSceneButtonPress(Node* node)
{
    // スタートボタンが押された時の処理
    startButtonPress(node);
    // ローカルDBデータの有無を確認
    if(!GameDataSQL::hasData()){
        // ユーザーがデータを作成していない場合はマイページのボタンを表示しない
        auto button = node->getChildByName<ui::Button*>("ui_mypage_btn");
        button->setVisible(false);
    } else {
        // サウンドの再生
        PlayerValue::getInstance()->dataLoad();
        if(PlayerValue::getInstance()->getSeOnOff()) {
            AudioManager::getInstance()->setSeVolume(100);
        } else {
            AudioManager::getInstance()->setSeVolume(0);
        }
        if(PlayerValue::getInstance()->getBgmOnOff()){
            AudioManager::getInstance()->setBgmVolume(100);
        }else{
            AudioManager::getInstance()->setBgmVolume(0);
        }
        // マイページのボタンが押された時の処理
        mypageButtonPress(node);
    }
    // その他のボタンが押された時の処理
    otherButtonPress(node);
    // デバッグボタンが押された時の処理
    debugButtonPress(node);
}

// スタートボタンが押された時の処理
void TitleScene::startButtonPress(Node* node)
{
    // ボタンノードを取得
    auto button = node->getChildByName<ui::Button*>("start_btn");
    // タッチイベント追加
    button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if(type == ui::Widget::TouchEventType::ENDED) {
            // 何度も押されないように一度押されたらアクションを無効にする
            this->getEventDispatcher()->removeAllEventListeners();
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
            // 0.5秒待ってからCallFuncを呼ぶ
            auto delay = DelayTime::create(0.2f);
            this->runAction(Sequence::create(delay, startGame, NULL));
        }
    });
}

// マイページのボタンが押された時の処理
void TitleScene::mypageButtonPress(Node* node)
{
    // ボタンノードを取得
    auto button = node->getChildByName<ui::Button*>("ui_mypage_btn");
    // タッチイベント追加
    button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if(type == ui::Widget::TouchEventType::ENDED) {
            // 何度も押されないように一度押されたらアクションを無効にする
            this->getEventDispatcher()->removeAllEventListeners();
            // マイページへの遷移
            auto transitionOtherScene = CallFunc::create([]{
                auto transition = TransitionFade::create(0.5f, MypageScene::createScene(MypageScene::transition_title), Color3B::WHITE);
                Director::getInstance()->replaceScene(transition);
            });
            // 0.5秒待ってからCallFuncを呼ぶ
            auto delay = DelayTime::create(0.2f);
            this->runAction(Sequence::create(delay, transitionOtherScene, NULL));
        }
    });
}

// その他のボタンが押された時の処理
void TitleScene::otherButtonPress(Node* node)
{
    // ボタンノードを取得
    auto button = node->getChildByName<ui::Button*>("ui_etc_btn");
    // タッチイベント追加
    button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if(type == ui::Widget::TouchEventType::ENDED) {
            // 何度も押されないように一度押されたらアクションを無効にする
            this->getEventDispatcher()->removeAllEventListeners();
            // その他メニューへの遷移
            auto transitionOtherScene = CallFunc::create([]{
                auto transition = TransitionFade::create(0.5f, OtherScene::createScene(OtherScene::transition_title), Color3B::WHITE);
                Director::getInstance()->replaceScene(transition);
            });
            // 0.5秒待ってからCallFuncを呼ぶ
            auto delay = DelayTime::create(0.2f);
            this->runAction(Sequence::create(delay, transitionOtherScene, NULL));
        }
    });
}

// デバッグボタンが押された時の処理
void TitleScene::debugButtonPress(Node* node)
{
    // ボタンノードを取得
    auto button = node->getChildByName<ui::Button*>("debug");
#if COCOS2D_DEBUG
    // タッチイベント追加
    button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if(type == ui::Widget::TouchEventType::ENDED) {
            // 何度も押されないように一度押されたらアクションを無効にする
            this->getEventDispatcher()->removeAllEventListeners();
            // サウンドを消す
            AudioManager::getInstance()->pauseBgm();
            Director::getInstance()->replaceScene(m_scene);
            m_projectController->getInstance();
        }
    });
#else
    button->setVisible(false);
#endif
}
