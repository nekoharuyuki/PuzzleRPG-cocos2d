#include "MenuLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "TitleScene.h"
#include "MypageScene.h"
#include "QuestScene.h"
#include "PartyScene.h"
#include "EvolutionScene.h"
#include "SyntheticScene.h"
#include "OtherScene.h"

#include "AudioManager.h"

USING_NS_CC;

using namespace cocostudio::timeline;

// on "init" you need to initialize your instance
bool MenuLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init()){
        return false;
    }
    
    auto rootNode = CSLoader::createNode("res/mypage/Menu.csb");
    if(rootNode == nullptr){
        return false;
    }
    this->addChild(rootNode);
    
    uiButtonPushLoadMypageScene(rootNode);
    uiButtonPushLoadQuestScene(rootNode);
    uiButtonPushLoadPartyScene(rootNode);
    uiButtonPushLoadMixScene(rootNode);
    uiButtonPushLoadShinkaScene(rootNode);
    uiButtonPushLoadOtherScene(rootNode);
    
    /*
    uiButtonPushLoadScene(rootNode, ui_mypage_btn, "ui_mypage_btn");
    uiButtonPushLoadScene(rootNode, ui_quest_btn,  "ui_quest_btn" );
    uiButtonPushLoadScene(rootNode, ui_party_btn,  "ui_party_btn" );
    uiButtonPushLoadScene(rootNode, ui_mix_btn,    "ui_mix_btn"   );
    uiButtonPushLoadScene(rootNode, ui_shinka_btn, "ui_shinka_btn");
    uiButtonPushLoadScene(rootNode, ui_etc_btn,    "ui_etc_btn"   );
    */
     
    this->scheduleUpdate();
    return true;
}

bool MenuLayer::uiButtonPushLoadScene(Node* node, Menu menu, const std::string& name)
{
    if(node == nullptr){
        return false;
    }
    // ボタンノードを取得
    auto btn = node->getChildByName<ui::Button*>(name);
    if(btn == nullptr){
        return false;
    }
    // タッチイベント追加
    btn->addTouchEventListener([this, menu](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        auto scene = loadScene(menu);
        if(scene){
            // シーンを切り替える
            auto startLoadScene = CallFunc::create([&scene]{
                auto transition = TransitionPageTurn::create(0.5f, scene, true);
                // ページをめくる音SE再生
                AudioManager::getInstance()->playSe("ui_page");
                Director::getInstance()->replaceScene(transition);
            });
            if(startLoadScene){
                this->runAction(Sequence::create(startLoadScene, NULL));
            }
        }
    });
    return true;
}

cocos2d::Scene* MenuLayer::loadScene(Menu menu)
{
    if( menu == ui_mypage_btn ){ return MypageScene::createScene(); }
    if( menu == ui_quest_btn  ){ return QuestScene::createScene();  }
    if( menu == ui_party_btn  ){ return PartyScene::createScene(); }
    if( menu == ui_mix_btn    ){ return SyntheticScene::createScene(); }
    if( menu == ui_shinka_btn ){ return EvolutionScene::createScene(); }
    if( menu == ui_etc_btn    ){ return OtherScene::createScene(OtherScene::transition_menu); }
    
    return nullptr;
}

bool MenuLayer::uiButtonPushLoadMypageScene(Node* node)
{
    if(node == nullptr){
        return false;
    }
    // ボタンノードを取得
    auto btn = node->getChildByName<ui::Button*>("ui_mypage_btn");
    if(btn == nullptr){
        return false;
    }
    // タッチイベント追加
    btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        // シーンを切り替える
        auto startLoadScene = CallFunc::create([]{
            auto scene = MypageScene::createScene();
            auto transition = TransitionPageTurn::create(0.5f, scene, true);
            // ページをめくる音SE再生
            AudioManager::getInstance()->playSe("ui_page");
            Director::getInstance()->replaceScene(transition);
        });
        if(startLoadScene){
            this->runAction(Sequence::create(startLoadScene, NULL));
        }
    });
    return true;
}

//-----

bool MenuLayer::uiButtonPushLoadQuestScene(Node* node)
{
    if(node == nullptr){
        return false;
    }
    // ボタンノードを取得
    auto btn = node->getChildByName<ui::Button*>("ui_quest_btn");
    if(btn == nullptr){
        return false;
    }
    // タッチイベント追加
    btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        // シーンを切り替える
        auto startLoadScene = CallFunc::create([]{
            auto scene = QuestScene::createScene();
            // ページをめくる音SE再生
            AudioManager::getInstance()->playSe("ui_page");
            auto transition = TransitionPageTurn::create(0.5f, scene, true);
            Director::getInstance()->replaceScene(transition);
        });
        if(startLoadScene){
            this->runAction(Sequence::create(startLoadScene, NULL));
        }
    });
    return true;
}

//-----

bool MenuLayer::uiButtonPushLoadPartyScene(Node* node)
{
    if(node == nullptr){
        return false;
    }
    // ボタンノードを取得
    auto btn = node->getChildByName<ui::Button*>("ui_party_btn");
    if(btn == nullptr){
        return false;
    }
    // タッチイベント追加
    btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        // シーンを切り替える
        auto startLoadScene = CallFunc::create([]{
            auto scene = PartyScene::createScene();
            // ページをめくる音SE再生
            AudioManager::getInstance()->playSe("ui_page");
            auto transition = TransitionPageTurn::create(0.5f, scene, true);
            Director::getInstance()->replaceScene(transition);
        });
        if(startLoadScene){
            this->runAction(Sequence::create(startLoadScene, NULL));
        }
    });
    return true;
}

//-----

bool MenuLayer::uiButtonPushLoadMixScene(Node* node)
{
    if(node == nullptr){
        return false;
    }
    // ボタンノードを取得
    auto btn = node->getChildByName<ui::Button*>("ui_mix_btn");
    if(btn == nullptr){
        return false;
    }
    // タッチイベント追加
    btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        // シーンを切り替える
        auto startLoadScene = CallFunc::create([]{
            auto scene = SyntheticScene::createScene();
            // ページをめくる音SE再生
            AudioManager::getInstance()->playSe("ui_page");
            auto transition = TransitionPageTurn::create(0.5f, scene, true);
            Director::getInstance()->replaceScene(transition);
        });
        if(startLoadScene){
            this->runAction(Sequence::create(startLoadScene, NULL));
        }
    });
    return true;
}

//-----

bool MenuLayer::uiButtonPushLoadShinkaScene(Node* node)
{
    if(node == nullptr){
        return false;
    }
    // ボタンノードを取得
    auto btn = node->getChildByName<ui::Button*>("ui_shinka_btn");
    if(btn == nullptr){
        return false;
    }
    // タッチイベント追加
    btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        // シーンを切り替える
        auto startLoadScene = CallFunc::create([]{
            auto scene = EvolutionScene::createScene();
            // ページをめくる音SE再生
            AudioManager::getInstance()->playSe("ui_page");
            auto transition = TransitionPageTurn::create(0.5f, scene, true);
            Director::getInstance()->replaceScene(transition);
        });
        if(startLoadScene){
            this->runAction(Sequence::create(startLoadScene, NULL));
        }
    });
    return true;
}

//-----

bool MenuLayer::uiButtonPushLoadOtherScene(Node* node)
{
    if(node == nullptr){
        return false;
    }
    // ボタンノードを取得
    auto btn = node->getChildByName<ui::Button*>("ui_etc_btn");
    if(btn == nullptr){
        return false;
    }
    // タッチイベント追加
    btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        // シーンを切り替える
        auto startLoadScene = CallFunc::create([]{
            auto scene = OtherScene::createScene(OtherScene::transition_menu);
            // ページをめくる音SE再生
            AudioManager::getInstance()->playSe("ui_page");
            auto transition = TransitionPageTurn::create(0.5f, scene, true);
            Director::getInstance()->replaceScene(transition);
        });
        if(startLoadScene){
            this->runAction(Sequence::create(startLoadScene, NULL));
        }
    });
    return true;
}
