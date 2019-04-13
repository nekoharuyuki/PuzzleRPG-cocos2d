#include "MypageScene.h"
#include "TitleScene.h"
#include "MenuLayer.h"
#include "PlayerValue.h"
#include "PartyValue.h"

USING_NS_CC;

using namespace cocostudio::timeline;

MypageScene::transition MypageScene::m_transitionScene;

//コンストラクタ
MypageScene::MypageScene()
{
}

Scene* MypageScene::createScene(MypageScene::transition sceneTransition)
{
    // どのシーンから遷移してきた
    m_transitionScene = sceneTransition;
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MypageScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MypageScene::onCreate()
{
    if ( !Layer::init() ){
        return false;
    }
    
    auto node = loaded();
    if(node == nullptr){
        return false;
    }
    
    if(m_transitionScene == transition_menu){
        // メニューレイヤーの初期化
        auto *layer = MenuLayer::create();
        if(layer == nullptr){
            return false;
        }
        // シーンにメニューレイヤーを追加する
        node->addChild(layer);
    }
    
    // タッチイベント追加
    auto titleBackBtn = node->getChildByName<ui::Button*>("TitleBack_btn");
    if(m_transitionScene == transition_title){
        titleBackBtn->setVisible(true);
        titleBackBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
            // 何度も押されないように一度押されたらアクションを無効にする
            this->getEventDispatcher()->removeAllEventListeners();
            // タイトルに戻る
            auto startLoadScene = CallFunc::create([]{
                auto scene = TitleScene::createScene();
                auto transition = TransitionFade::create(0.5f, scene, Color3B::WHITE);
                Director::getInstance()->replaceScene(transition);
            });
            this->runAction(Sequence::create(startLoadScene, NULL));
        });
    } else {
        titleBackBtn->setVisible(false);
    }
    
    // ユーザーデータの読み込み
    if(!onCreatePlayerValue(node)){
        return false;
    }
    
    // パーティデータ読込み表示
    if(!onCreatePartyValue(node)){
        return false;
    }
    
    return true;
}

// ユーザーデータの読み込み
bool MypageScene::onCreatePlayerValue(Node* node)
{
    PlayerValue::getInstance()->dataLoad();
    
    auto CoinText = node->getChildByName<ui::Text*>( "CoinText" );
    if(CoinText){
        CoinText->setString( std::to_string(PlayerValue::getInstance()->getCoin()) );
        return true;
    }
    return false;
}

// パーティデータ読込み表示
bool MypageScene::onCreatePartyValue(Node* node)
{
    PartyValue::getInstance()->dataLoad();
    
    for(int i = 0; i < 3; i++){
        //        auto CharIconNode = rootNode->getChildByName<Node*>( "CharIconNode"+std::to_string(i) );
        auto CharLv = node->getChildByName<ui::Text*>( "CharLv"+std::to_string(i) );
        auto CharName = node->getChildByName<ui::Text*>( "CharName"+std::to_string(i) );
        
        CharLv->setString( " " );
        CharName->setString( " " );
    }
    /*
     auto Atk = new Array();
     auto CharName = new Array();
     for(i = 0; i < 3; i++){
     cc.log(i);
     Atk[i] = rootNode->getChildByName<ui::Text*>( "Atk"+i );
     Atk[i].setString( getAtk(i) );
     }
     */
    auto PartyHpText = node->getChildByName<ui::Text*>( "PartyHpText" );
    PartyHpText->setString( "100" );
    return true;
}
