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
#include "CharIconSprite.h"
#include "AudioManager.h"

USING_NS_CC;

#define MOTION_STREAK_TAG 10

using namespace cocostudio::timeline;

PartyScene::PartyScene()
: m_touchable(true)
, m_currentPos(0)
, m_currentLimit(0)
{
}

PartyScene::~PartyScene()
{
    // データを保存する
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
    
    //パーティデータ表示
    initParty(paty_base, partyValue);
    initStorage(paty_base, partyValue);
    
    auto right_btn = paty_base->getChildByName<ui::Button*>( "right_btn" );
    right_btn->addTouchEventListener([this,paty_base](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
            onRight(paty_base);
        }
    });
    auto left_btn = paty_base->getChildByName<ui::Button*>( "left_btn" );
    left_btn->addTouchEventListener([this,paty_base](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
            onLeft(paty_base);
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

void PartyScene::initParty(Node* node, PartyValue* partyValue)
{
    //パーティデータ読込み表示
    for(int i = 0; i < 3; i++){
        auto CharLv = node->getChildByName<ui::Text*>( "leveltext"+std::to_string(i) );
        auto CharName = node->getChildByName<ui::Text*>( "nametext"+std::to_string(i) );
        int storageId = partyValue->getPartyMemberForStorageId(i);
        auto CharIconNode = node->getChildByName<Node*>( "party"+std::to_string(i) );
        if(CharIconNode){
            int charId = partyValue->getCharStorageFromCharId(storageId);
            if(storageId != 0){
                int charLevel = partyValue->getCharStorageFromCharLevel(storageId);
                auto charDataParam = CharData::getCharData(charId);
                auto charaPlayerSprite = CharIconSprite::create(charId+1, CharIconSprite::CharType::Member);
                if(charaPlayerSprite){
                    CharIconNode->setVisible(true);
                    CharIconNode->addChild( charaPlayerSprite );
                    m_partyList[i].sprite = charaPlayerSprite;
                }
                CharLv->setString( "Lv"+std::to_string(charLevel) );
                CharName->setString( charDataParam.charName );
            } else {
                auto charaPlayerSprite = CharIconSprite::create(0, CharIconSprite::CharType::Member);
                if(charaPlayerSprite){
                    CharIconNode->setVisible(false);
                    CharIconNode->addChild( charaPlayerSprite );
                    m_partyList[i].sprite = charaPlayerSprite;
                }
                CharLv->setString( " " );
                CharName->setString( " " );
            }
            m_partyList[i].charId = charId;
            m_partyList[i].storageId = storageId;
        }
    }
    
    auto hptext = node->getChildByName<ui::Text*>( "hptext" );
    hptext->setString( std::to_string(partyValue->getTotalHp()) );
    auto atktext0 = node->getChildByName<ui::Text*>( "atktext0" );
    atktext0->setString( std::to_string(partyValue->getAtk(1)) );
    auto atktext1 = node->getChildByName<ui::Text*>( "atktext1" );
    atktext1->setString( std::to_string(partyValue->getAtk(2)) );
    auto atktext2 = node->getChildByName<ui::Text*>( "atktext2" );
    atktext2->setString( std::to_string(partyValue->getAtk(3)) );
    auto healingtext = node->getChildByName<ui::Text*>( "healingtext" );
    healingtext->setString( std::to_string(partyValue->getTotalAtk()) );
}

void PartyScene::initStorage(Node* node, PartyValue* partyValue)
{
    int maxStorage = partyValue->getMaxStorageId();
    int viewCount = 0;
    for(int i = 1; i < maxStorage; i++ ){
        bool isPartyMember = partyValue->isPartyMembercharacter(i);
        if(!isPartyMember){
            int charId = partyValue->getCharStorageFromCharId(i);
            if(viewCount < 5){
                auto stockIconNode = node->getChildByName<Node*>( "stock"+std::to_string(viewCount) );
                auto charaPlayerSprite = CharIconSprite::create(charId+1, CharIconSprite::CharType::Member);
                if(charaPlayerSprite){
                    stockIconNode->addChild( charaPlayerSprite );
                    m_stockList[viewCount].sprite = charaPlayerSprite;
                }
            }
            m_stockList[viewCount].charId = charId;
            m_stockList[viewCount].storageId = i;
            viewCount++;
        }
    }
}

bool PartyScene::onTouchBegan(Touch* touch, Event* unused_event)
{
    if (!m_touchable){
        return false;
    }
    // 指でなぞったラインを描画する
    this->removeChildByTag(MOTION_STREAK_TAG, true);
    Point point = this->convertTouchToNodeSpace(touch);
    MotionStreak* pStreak = MotionStreak::create(0.5f, 1.0f, 10.0f, Color3B(255, 255, 0), "system/images/line.png");
    pStreak->setPosition(point);
    this->addChild(pStreak, 10, MOTION_STREAK_TAG);
    
    return true;
}

void PartyScene::onTouchMoved(Touch* touch, Event* unused_event)
{
    if (!m_touchable){
        return;
    }
    // 指でなぞったラインを描画する
    Point point = this->convertTouchToNodeSpace(touch);
    MotionStreak* pStreak = (MotionStreak*)this->getChildByTag(MOTION_STREAK_TAG);
    pStreak->setPosition(point);
}

void PartyScene::onTouchEnded(Touch* touch, Event* unused_event)
{
    if (!m_touchable){
        return;
    }
}

void PartyScene::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}

bool PartyScene::isTouchPartyIcon(cocos2d::Touch* touch)
{
    Vec2 location = touch->getLocation();
    for (int i = 0; i < (int)m_stockList.size(); i ++) {
        Sprite *item = m_stockList[i].sprite;
        Rect spriteRect = Rect(item->getPosition().x - item->getContentSize().width/2,
                               item->getPosition().y - item->getContentSize().width/2,
                               item->getContentSize().width,
                               item->getContentSize().height);
        if (spriteRect.containsPoint(location)) {
            item->setVisible(false);
            return true;
        }
    }
    return false;
}

bool PartyScene::isTouchStorageIcon(cocos2d::Touch* touch)
{
    Vec2 location = touch->getLocation();
    for (int i = 0; i < (int)m_partyList.size(); i ++) {
        Sprite *item = m_partyList[i].sprite;
        Rect spriteRect = Rect(item->getPosition().x - item->getContentSize().width/2,
                               item->getPosition().y - item->getContentSize().width/2,
                               item->getContentSize().width,
                               item->getContentSize().height);
        if (spriteRect.containsPoint(location)) {
            item->setVisible(false);
            return true;
        }
    }
    return false;
}

void PartyScene::onRight(Node* node)
{
    if (!m_touchable){
        return;
    }
    AudioManager::getInstance()->playSe("cur");
    m_currentPos--;
    setStockIcon(node);
}

void PartyScene::onLeft(Node* node)
{
    if (!m_touchable){
        return;
    }
    AudioManager::getInstance()->playSe("cur");
    m_currentPos++;
    setStockIcon(node);
}

void PartyScene::setStockIcon(Node* node)
{
    if( m_currentPos > 0 ){
        m_currentPos = 0;
    }
    if(m_currentLimit != 0 && m_currentPos < m_currentLimit){
        m_currentPos = m_currentLimit;
    }
    for(int i = 0; i < 5; i++ ){
        auto stockIconNode = node->getChildByName<Node*>( "stock"+std::to_string(i) );
        if(stockIconNode){
            int current = (5 + i) - (5 + m_currentPos);
            if(m_stockList[current].storageId != 0){
                auto charaPlayerSprite = CharIconSprite::create(m_stockList[current].charId+1, CharIconSprite::CharType::Member);
                if(charaPlayerSprite){
                    stockIconNode->setVisible(true);
                    stockIconNode->addChild( charaPlayerSprite );
                }
            } else {
                auto charaPlayerSprite = CharIconSprite::create(0, CharIconSprite::CharType::Member);
                if(charaPlayerSprite){
                    stockIconNode->setVisible(false);
                    stockIconNode->addChild( charaPlayerSprite );
                }
                m_currentLimit = m_currentPos;
            }
        }
    }
}

void PartyScene::updateParty()
{
    auto partyValue = PartyValue::getInstance();
    if(!partyValue){
        return;
    }
    
    
    
    partyValue->dataSave();
}

void PartyScene::updateStorage()
{
    auto partyValue = PartyValue::getInstance();
    if(!partyValue){
        return;
    }
    
    
    
    partyValue->dataSave();
}

void PartyScene::onShowStatus(int id)
{
    
}
