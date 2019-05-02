//
//  PartyScene.h
//  PuzzleRPG
//
//  Created by neko on 2019/02/02.
//

#include "PartyScene.h"
#include "MenuLayer.h"
#include "CharData.h"
#include "PlayerValue.h"
#include "PartyValue.h"
#include "BattleCharIconSprite.h"
#include "AudioManager.h"

USING_NS_CC;

#define MOTION_STREAK_TAG 10

using namespace cocostudio::timeline;

PartyScene::PartyScene()
: m_touchable(true)
{
}

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
    auto paty_base = node->getChildByName("paty_base");
    //auto DragNode = paty_base->getChildByName("DragNode");
    
    //パーティデータ読み込み
    auto partyValue = PartyValue::getInstance();
    if(!partyValue){
        return false;
    }
    partyValue->dataLoad();
    
    //パーティデータ読込み表示
    for(int i = 0; i < 3; i++){
        auto CharLv = paty_base->getChildByName<ui::Text*>( "leveltext"+std::to_string(i) );
        auto CharName = paty_base->getChildByName<ui::Text*>( "nametext"+std::to_string(i) );
        int storageId = partyValue->getPartyMemberForStorageId(i);
        if(storageId != 0){
            int charId = partyValue->getCharStorageFromCharId(storageId);
            int charLevel = partyValue->getCharStorageFromCharLevel(storageId);
            auto charDataParam = CharData::getCharData(charId);
            CharLv->setString( "Lv"+std::to_string(charLevel) );
            CharName->setString( charDataParam.charName );
            auto CharIconNode = paty_base->getChildByName<Node*>( "party"+std::to_string(i) );
            if(CharIconNode){
                auto charaPlayerSprite = BattleCharIconSprite::create(charId+1, BattleCharIconSprite::CharType::Member);
                if(charaPlayerSprite){
                    CharIconNode->addChild( charaPlayerSprite );
                }
            }
        } else {
            CharLv->setString( " " );
            CharName->setString( " " );
        }
    }
    
    auto hptext = paty_base->getChildByName<ui::Text*>( "hptext" );
    hptext->setString( std::to_string(partyValue->getTotalHp()) );
    auto atktext0 = paty_base->getChildByName<ui::Text*>( "atktext0" );
    atktext0->setString( std::to_string(partyValue->getAtk(1)) );
    auto atktext1 = paty_base->getChildByName<ui::Text*>( "atktext1" );
    atktext1->setString( std::to_string(partyValue->getAtk(2)) );
    auto atktext2 = paty_base->getChildByName<ui::Text*>( "atktext2" );
    atktext2->setString( std::to_string(partyValue->getAtk(3)) );
    auto healingtext = paty_base->getChildByName<ui::Text*>( "healingtext" );
    healingtext->setString( std::to_string(partyValue->getTotalAtk()) );
    
    
    
    
    auto right_btn = paty_base->getChildByName<ui::Button*>( "right_btn" );
    right_btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
            onRight();
        }
    });
    auto left_btn = paty_base->getChildByName<ui::Button*>( "left_btn" );
    left_btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
            onLeft();
        }
    });
    
    // シングルタップイベントの取得
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(_swallowsTouches);
    touchListener->onTouchBegan = CC_CALLBACK_2(PartyScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PartyScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PartyScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(PartyScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

bool PartyScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    // 指でなぞったラインを描画する
    this->removeChildByTag(MOTION_STREAK_TAG, true);
    
    Point point = this->convertTouchToNodeSpace(touch);
    MotionStreak* pStreak = MotionStreak::create(0.5f, 1.0f, 10.0f, Color3B(255, 255, 0), "system/images/line.png");
    pStreak->setPosition(point);
    this->addChild(pStreak, 10, MOTION_STREAK_TAG);
    
    if (!m_touchable){
        return false;
    }
    
    return true;
}

void PartyScene::onTouchMoved(Touch* touch, Event* unused_event)
{
    // 指でなぞったラインを描画する
    Point point = this->convertTouchToNodeSpace(touch);
    MotionStreak* pStreak = (MotionStreak*)this->getChildByTag(MOTION_STREAK_TAG);
    pStreak->setPosition(point);
}

void PartyScene::onTouchEnded(Touch* touch, Event* unused_event)
{
}

void PartyScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}

void PartyScene::onRight()
{
    AudioManager::getInstance()->playSe("cur");
}

void PartyScene::onLeft()
{
    AudioManager::getInstance()->playSe("cur");
}

void PartyScene::onShowStatus(int id)
{
    
}

void PartyScene::updateStorage()
{
    
}
