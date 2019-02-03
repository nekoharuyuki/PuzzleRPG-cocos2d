//
//  PartyScene.h
//  PuzzleRPG
//
//  Created by neko on 2019/02/02.
//

#include "PartyScene.h"
#include "MenuLayer.h"
#include "PartyValue.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* PartyScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = PartyScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PartyScene::onCreate()
{
    if ( !Layer::init() ){
        return false;
    }
    
    auto node = loaded();
    if(node == nullptr){
        return false;
    }
    
    // レイヤーの初期化
    auto *layer = MenuLayer::create();
    if(layer == nullptr){
        return false;
    }
    // シーンにレイヤーを追加する
    node->addChild(layer);
    
    auto chara_statusbase = node->getChildByName("chara_statusbase");
    chara_statusbase->setVisible(false);
    auto conform = node->getChildByName("conform");
    conform->setVisible(false);
    //auto paty_base = node->getChildByName("paty_base");
    //auto DragNode = paty_base->getChildByName("DragNode");
    
    //パーティデータ読み込み
    auto partyValue = PartyValue::getInstance();
    partyValue->dataLoad();
    
    return true;
}
