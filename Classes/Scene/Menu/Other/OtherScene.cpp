#include "OtherScene.h"
#include "TitleScene.h"
#include "MenuLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* OtherScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OtherScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OtherScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("other/OtherScene.csb");
    if(rootNode == nullptr){
        return false;
    }
    this->addChild(rootNode);
    
    // レイヤーの初期化
    auto *layer = MenuLayer::create();
    if(layer == nullptr){
        return false;
    }
    // シーンにレイヤーを追加する
    rootNode->addChild(layer);
    
    // ボタンノードを取得
    auto popupOther = rootNode->getChildByName("popup_other");
    auto btn = popupOther->getChildByName<ui::Button*>("TitleBack_btn");
    // タッチイベント追加
    btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        // ゲームを始めるアクション
        auto startLoadScene = CallFunc::create([]{
            auto scene = TitleScene::createScene();
            auto transition = TransitionPageTurn::create(0.5f, scene, true);
            Director::getInstance()->replaceScene(transition);
        });
        this->runAction(Sequence::create(startLoadScene, NULL));
        return true;    // イベントを実行する
    });
    
    return true;
}
