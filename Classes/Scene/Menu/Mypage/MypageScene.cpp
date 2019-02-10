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
    
    PlayerValue::getInstance()->dataLoad();
    
    auto CoinText = node->getChildByName<ui::Text*>( "CoinText" );
    if(CoinText){
        CoinText->setString( std::to_string(PlayerValue::getInstance()->getCoin()) );
    }
    
    //パーティデータ読込み表示
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
