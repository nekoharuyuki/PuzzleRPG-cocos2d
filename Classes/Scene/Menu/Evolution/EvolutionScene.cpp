#include "EvolutionScene.h"
#include "MenuLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* EvolutionScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EvolutionScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EvolutionScene::onCreate()
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
    
    return true;
}
