#include "MypageScene.h"
#include "TitleScene.h"
#include "MenuLayer.h"
#include "PlayerValue.h"
#include "PartyValue.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MypageScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MypageScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MypageScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ){
        return false;
    }
    
    auto rootNode = CSLoader::createNode("mypage/MypageScene.csb");
    if(rootNode == nullptr){
        return false;
    }
    this->addChild(rootNode);
    
    // レイヤーの初期化
    auto *layer = MenuLayer::create();
    if(layer == nullptr){
        return false;
    }
    
    PlayerValue::getInstance()->dataLoad();
    
    auto CoinText = rootNode->getChildByName<ui::Text*>( "CoinText" );
    if(CoinText){
        CoinText->setString( std::to_string(PlayerValue::getInstance()->getCoin()) );
    }
    
    //パーティデータ読込み表示
    PartyValue::getInstance()->dataLoad();
    
    for(int i = 0; i < 3; i++){
//        auto CharIconNode = rootNode->getChildByName<Node*>( "CharIconNode"+std::to_string(i) );
        auto CharLv = rootNode->getChildByName<ui::Text*>( "CharLv"+std::to_string(i) );
        auto CharName = rootNode->getChildByName<ui::Text*>( "CharName"+std::to_string(i) );
        
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
    auto PartyHpText = rootNode->getChildByName<ui::Text*>( "PartyHpText" );
    PartyHpText->setString( std::to_string(PartyValue::getInstance()->getTotalHp()) );
    
    // シーンにレイヤーを追加する
    rootNode->addChild(layer);
    
    return true;
}
