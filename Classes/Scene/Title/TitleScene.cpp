#include "TitleScene.h"
#include "QuestScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

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
    
    auto rootNode = CSLoader::createNode("title/TitleScene.csb");
    if(rootNode == nullptr){
        return false;
    }
    addChild(rootNode);
    
    // セーブデータの有無を確認
    
    
    // ボタンノードを取得
    auto startBtn = rootNode->getChildByName<ui::Button*>("start_btn");
    // タッチイベント追加
    startBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        
        // 0.5秒待ってからCallFuncを呼ぶ
        auto delay = DelayTime::create(0.5f);
        
        // ゲームを始めるアクション
        auto startGame = CallFunc::create([]{
            auto scene = QuestScene::createScene();
            auto transition = TransitionFade::create(0.5f, scene, Color3B::WHITE);
            Director::getInstance()->replaceScene(transition);
        });
        this->runAction(Sequence::create(delay, startGame, NULL));
        return true;    // イベントを実行する
    });
    
    this->scheduleUpdate();
    return true;
}

