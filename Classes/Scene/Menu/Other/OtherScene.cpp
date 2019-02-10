#include "OtherScene.h"
#include "TitleScene.h"
#include "MenuLayer.h"
#include "GameDataSQL.h"
#include "PlayerValue.h"
#include "cocostudio/CocoStudio.h"
#include "AudioManager.h"

USING_NS_CC;

using namespace cocostudio::timeline;

OtherScene::transition OtherScene::m_transitionScene;

bool OtherScene::m_bgm = true;
bool OtherScene::m_se  = true;

//コンストラクタ
OtherScene::OtherScene()
: m_seOn(nullptr)
, m_seOff(nullptr)
, m_bgmOn(nullptr)
, m_bgmOff(nullptr)
{
}

Scene* OtherScene::createScene(OtherScene::transition sceneTransition)
{
    // どのシーンから遷移してきた
    m_transitionScene = sceneTransition;
    
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
bool OtherScene::onCreate()
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
    
    // ローカルDBデータの有無を確認
    if(GameDataSQL::hasData()){
        PlayerValue::getInstance()->dataLoad();
        int seOnOff = PlayerValue::getInstance()->getSeOnOff();
        int bgmOnOff = PlayerValue::getInstance()->getBgmOnOff();
        m_se = seOnOff;
        m_bgm = bgmOnOff;
    }
    
    // ボタンノードを取得
    auto popupOther = node->getChildByName("popup_other");
    
    // タッチイベント追加
    m_seOn = popupOther->getChildByName<ui::Button*>("se_on");
    m_seOn->setBright( !m_se );
    m_seOn->setEnabled( !m_se );
    m_seOn->addTouchEventListener(CC_CALLBACK_2(OtherScene::onSeOnOff, this));
    m_seOff = popupOther->getChildByName<ui::Button*>("se_off");
    m_seOff->setBright( m_se );
    m_seOff->setEnabled( m_se );
    m_seOff->addTouchEventListener(CC_CALLBACK_2(OtherScene::onSeOnOff, this));
    
    // タッチイベント追加
    m_bgmOn = popupOther->getChildByName<ui::Button*>("bgm_on");
    m_bgmOn->setBright( !m_bgm );
    m_bgmOn->setEnabled( !m_bgm );
    m_bgmOn->addTouchEventListener(CC_CALLBACK_2(OtherScene::onBgmOnOff, this));
    m_bgmOff = popupOther->getChildByName<ui::Button*>("bgm_off");
    m_bgmOff->setBright( m_bgm );
    m_bgmOff->setEnabled( m_bgm );
    m_bgmOff->addTouchEventListener(CC_CALLBACK_2(OtherScene::onBgmOnOff, this));
    
    // タッチイベント追加
    auto titleBackBtn = popupOther->getChildByName<ui::Button*>("TitleBack_btn");
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
    
    return true;
}

void OtherScene::onSeOnOff(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type){
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
        m_se = !m_se;
        m_seOn->setBright( !m_se );
        m_seOn->setEnabled( !m_se );
        m_seOff->setBright( m_se );
        m_seOff->setEnabled( m_se );
        if( m_se ){
            AudioManager::getInstance()->setSeVolume(100);
            GameDataSQL::sqliteUpdateValueForKey("SeOnOff", std::to_string(1).c_str());
        }else{
            AudioManager::getInstance()->setSeVolume(0);
            GameDataSQL::sqliteUpdateValueForKey("SeOnOff", std::to_string(0).c_str());
        }
        AudioManager::getInstance()->playSe("cur");
    }
}

void OtherScene::onBgmOnOff(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type){
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
        m_bgm = !m_bgm;
        m_bgmOn->setBright( !m_bgm );
        m_bgmOn->setEnabled( !m_bgm );
        m_bgmOff->setBright( m_bgm );
        m_bgmOff->setEnabled( m_bgm );
        if( m_bgm ){
            AudioManager::getInstance()->setBgmVolume(100);
            GameDataSQL::sqliteUpdateValueForKey("BgmOnOff", std::to_string(1).c_str());
        }else{
            AudioManager::getInstance()->setBgmVolume(0);
            GameDataSQL::sqliteUpdateValueForKey("BgmOnOff", std::to_string(0).c_str());
        }
        AudioManager::getInstance()->playSe("cur");
    }
}
