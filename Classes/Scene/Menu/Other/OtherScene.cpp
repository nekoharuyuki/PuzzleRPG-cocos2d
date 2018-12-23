#include "OtherScene.h"
#include "TitleScene.h"
#include "MenuLayer.h"
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
    
    if(m_transitionScene == transition_menu){
        // メニューレイヤーの初期化
        auto *layer = MenuLayer::create();
        if(layer == nullptr){
            return false;
        }
        // シーンにメニューレイヤーを追加する
        rootNode->addChild(layer);
    }
    // ボタンノードを取得
    auto popupOther = rootNode->getChildByName("popup_other");
    
    // タッチイベント追加
    m_seOn = popupOther->getChildByName<ui::Button*>("se_on");
    m_seOn->addTouchEventListener(CC_CALLBACK_2(OtherScene::onSeOnOff, this));
    m_seOff = popupOther->getChildByName<ui::Button*>("se_off");
    m_seOff->addTouchEventListener(CC_CALLBACK_2(OtherScene::onSeOnOff, this));
    m_seOn->setBright( !m_se );
    m_seOn->setEnabled( !m_se );
    m_seOff->setBright( m_se );
    m_seOff->setEnabled( m_se );
    
    // タッチイベント追加
    m_bgmOn = popupOther->getChildByName<ui::Button*>("bgm_on");
    m_bgmOn->addTouchEventListener(CC_CALLBACK_2(OtherScene::onBgmOnOff, this));
    m_bgmOff = popupOther->getChildByName<ui::Button*>("bgm_off");
    m_bgmOff->addTouchEventListener(CC_CALLBACK_2(OtherScene::onBgmOnOff, this));
    m_bgmOn->setBright( !m_bgm );
    m_bgmOn->setEnabled( !m_bgm );
    m_bgmOff->setBright( m_bgm );
    m_bgmOff->setEnabled( m_bgm );
    
    // タッチイベント追加
    auto titleBackBtn = popupOther->getChildByName<ui::Button*>("TitleBack_btn");
    titleBackBtn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        // 何度も押されないように一度押されたらアクションを無効にする
        this->getEventDispatcher()->removeAllEventListeners();
        // ゲームを始めるアクション
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
        }else{
            AudioManager::getInstance()->setSeVolume(0);
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
        }else{
            AudioManager::getInstance()->setBgmVolume(0);
        }
        AudioManager::getInstance()->playSe("cur");
    }
}
