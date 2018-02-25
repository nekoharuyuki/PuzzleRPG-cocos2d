#include "QuestScene.h"
#include "MenuLayer.h"
#include "PuzzleGameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

QuestScene::QuestScene()
: m_questNo(0)
{
}

Scene* QuestScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = QuestScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool QuestScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ){
        return false;
    }
    
    auto rootNode = CSLoader::createNode("quest/QuestScene.csb");
    if(rootNode == nullptr){
        return false;
    }
    this->addChild(rootNode);
    
    for(m_questNo = 0; m_questNo < 30; m_questNo++){
        auto questNode = rootNode->getChildByName<Node*>("quest_"+std::to_string(m_questNo+1));
        if(questNode == nullptr){
            break;
        }
        
        auto quest_btn = questNode->getChildByName<ui::Button*>("quest_btn");
        
        // ユーザーデータを確認して、クエストの表示状況を変更する
        quest_btn->setBright(true);
        quest_btn->setEnabled(true);

        //quest_btn->addTouchEventListener( this.onQuest, this );
        
        // タッチイベント追加
        quest_btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            // 何度も押されないように一度押されたらアクションを無効にする
            this->getEventDispatcher()->removeAllEventListeners();
            
            // 0.5秒待ってからCallFuncを呼ぶ
            auto delay = DelayTime::create(0.5f);
            
            // ゲームを始めるアクション
            auto startGame = CallFunc::create([delay]{
                auto scene = PuzzleGameScene::createScene();
                auto transition = TransitionFadeTR::create(0.5f, scene);
                Director::getInstance()->replaceScene(transition);
            });
            this->runAction(Sequence::create(delay, startGame, NULL));
            return true;    // イベントを実行する
        });
        
    }
    
    // レイヤーの初期化
    auto *layer = MenuLayer::create();
    if(layer == nullptr){
        return false;
    }
    // シーンにレイヤーを追加する
    rootNode->addChild(layer);
    
    return true;
}
