#include "QuestScene.h"
#include "MapData.h"
#include "MenuLayer.h"
#include "PlayerValue.h"
#include "PuzzleGameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "AudioManager.h"

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
    
    // クエスト選択時のポップアップを非表示にする
    m_popup_quest = rootNode->getChildByName<Node*>( "popup_quest" );
    m_popup_quest->setVisible(false);
    
    //クエストマスの初期化
    initQuestmas(rootNode);
    
    // レイヤーの初期化
    auto *layer = MenuLayer::create();
    if(layer == nullptr){
        return false;
    }
    // シーンにレイヤーを追加する
    rootNode->addChild(layer);
    
    return true;
}

//クエストマスの初期化
void QuestScene::initQuestmas(Node* node)
{
    // ユーザーデータ作成
    PlayerValue::getInstance()->dataLoad();
    int clearMap = PlayerValue::getInstance()->getClearMap();
    
    for(int i = 0; i < 30; i++){
        auto questNode = node->getChildByName<Node*>("quest_"+std::to_string(i+1));
        if(questNode == nullptr){
            break;
        }
        
        auto quest_btn = questNode->getChildByName<ui::Button*>("quest_btn");
        
        // ユーザーデータを確認して、クエストの表示状況を変更する
        if(i <= clearMap){
            // Mapに挑戦出来る
            quest_btn->setBright(true);
            quest_btn->setEnabled(true);
        } else {
            // Mapに挑戦出来ない
            quest_btn->setBright(false);
            quest_btn->setEnabled(false);
        }
        
        // タッチイベント追加
        quest_btn->addTouchEventListener([this, i](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
                m_questNo = i;
                onQuest();
            }
        });
    }
}

void QuestScene::onQuest()
{
    if(m_popup_quest->isVisible() == true){
        return;
    }
    
    // ポップアップ表示音 再生
    AudioManager::getInstance()->playSe("window");
    
    m_popup_quest->setVisible(true);
    
    auto quest_btn = m_popup_quest->getChildByName<ui::Button*>( "QuestStart_btn" );
    quest_btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
            onQuestStart();
        }
    });
    auto Back_btn = m_popup_quest->getChildByName<ui::Button*>( "Back_btn" );
    Back_btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
            onBack();
        }
    });
    auto nametext = m_popup_quest->getChildByName<ui::Text*>( "nametext" );
    nametext->setString( MapData::getMapData(m_questNo).mapName );
}

void QuestScene::onQuestStart()
{
    // 何度も押されないように一度押されたらアクションを無効にする
    this->getEventDispatcher()->removeAllEventListeners();
    
    // BGMをフェードアウトをしながら停止
    AudioManager::getInstance()->stopBgm(0.3f);
    
    // エリア移動BGM再生
    AudioManager::getInstance()->playSe("area1");
    
    // 0.5秒待ってからCallFuncを呼ぶ
    auto delay = DelayTime::create(0.5f);
    
    // ゲームを始めるアクション
    auto startGame = CallFunc::create([this]{
        auto scene = PuzzleGameScene::createScene(m_questNo);
        auto transition = TransitionFadeTR::create(0.5f, scene);
        Director::getInstance()->replaceScene(transition);
    });
    this->runAction(Sequence::create(delay, startGame, NULL));
}

void QuestScene::onBack()
{
    // キャンセル音 再生
    AudioManager::getInstance()->playSe("cansell");
    
    m_popup_quest->setVisible(false);
}
