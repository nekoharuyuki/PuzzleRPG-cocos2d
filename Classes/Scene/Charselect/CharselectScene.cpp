//
//  CharselectScene.cpp
//  PuzzleRPG
//
//  Created by neko on 2018/03/25.
//

#include "CharselectScene.h"
#include "QuestScene.h"
#include "PlayerValue.h"
#include "PartyValue.h"
#include "CharData.h"
#include "CharSelectSprite.h"
#include "CharIconSprite.h"
#include "GameDataSQL.h"
#include "AudioManager.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* CharselectScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CharselectScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool CharselectScene::onCreate()
{
    if ( !Layer::init() ){
        return false;
    }
    auto node = loaded();
    if(node == nullptr){
        return false;
    }
    
    m_popup_1 = node->getChildByName<Node*>( "popup_1" );
    m_popup_1->setVisible(true);
    auto char1_btn = m_popup_1->getChildByName<ui::Button*>( "char1_btn" );
    char1_btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
            onChar( SelectCharNo01 );
        }
    });
    auto char2_btn = m_popup_1->getChildByName<ui::Button*>( "char2_btn" );
    char2_btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
            onChar( SelectCharNo02 );
        }
    });
    auto char3_btn = m_popup_1->getChildByName<ui::Button*>( "char3_btn" );
    char3_btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
            onChar( SelectCharNo03 );
        }
    });
    
    m_popup_2 = node->getChildByName<Node*>( "popup_2" );
    m_popup_2->setVisible(false);
    m_popup_3 = node->getChildByName<Node*>( "popup_3" );
    m_popup_3->setVisible(false);
    
    this->scheduleUpdate();
    return true;
}

void CharselectScene::onChar( SelectCharNo no )
{
    AudioManager::getInstance()->playSe("ui_title_start");
    m_popup_1->setVisible(false);
    
    auto yes_btn = m_popup_2->getChildByName<ui::Button*>( "yes_btn" );
    yes_btn->addTouchEventListener([this, no](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
            onYes(no);
        }
    });
    
    auto back_btn = m_popup_2->getChildByName<ui::Button*>( "back_btn" );
    back_btn->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
            onBack();
        }
    });
    
    auto NameText = m_popup_2->getChildByName<ui::Text*>( "NameText" );
    if(NameText){
        NameText->setString( CharData::getCharData(no).charName );
    }
    auto AttributeNode = m_popup_2->getChildByName<Node*>( "AttributeNode" );
    if(AttributeNode){
        auto charIconSprite = BattleCharIconSprite::create(CharData::getCharData(no).charId, BattleCharIconSprite::CharType::Member);
        if(charIconSprite){
            charIconSprite->setScale(0.5f);
            AttributeNode->addChild( charIconSprite, 1 );
        }
    }
    auto AtkText = m_popup_2->getChildByName<ui::Text*>( "AtkText" );
    if(AtkText){
        AtkText->setString( std::to_string(CharData::getCharData(no).charAtk) );
    }
    auto SkillText = m_popup_2->getChildByName<ui::Text*>( "SkillText" );
    if(SkillText){
        SkillText->setString( CharData::getCharData(no).charSkillText );
    }
    auto chara_princessselect = m_popup_2->getChildByName<Node*>( "chara_princessselect" );
    if(chara_princessselect){
        chara_princessselect->removeAllChildren();
        auto charSprite = CharSelectSprite::create(CharData::getCharData(no).charId);
        if(charSprite){
            chara_princessselect->addChild( charSprite, 1 );
        }
    }
    m_popup_2->setVisible(true);
}

void CharselectScene::onYes(SelectCharNo no)
{
    m_popup_2->setVisible(false);
    auto start_btn = m_popup_3->getChildByName<ui::Button*>( "start_btn" );
    start_btn->addTouchEventListener([this, no](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED){
            onStart(no);
        }
    });
    
    auto NameText = m_popup_3->getChildByName<ui::Text*>( "NameText" );
    NameText->setString( CharData::getCharData(no).charName );
    auto IconCharaNode = m_popup_3->getChildByName<Node*>( "IconCharaNode" );
    auto charIconSprite = BattleCharIconSprite::create(CharData::getCharData(no).charId, BattleCharIconSprite::CharType::Member);
    if(charIconSprite){
        charIconSprite->setScale(0.5f);
        IconCharaNode->addChild( charIconSprite, 1 );
    }
    auto chara_princessselect = m_popup_3->getChildByName<ui::Button*>( "chara_princessselect" );
    auto charSprite = CharSelectSprite::create(CharData::getCharData(no).charId);
    if(charSprite){
        chara_princessselect->addChild( charSprite, 1 );
    }
    
    m_popup_3->setVisible(true);
}

void CharselectScene::onBack()
{
    // キャンセル音 再生
    AudioManager::getInstance()->playSe("cansell");
    
    m_popup_1->setVisible(true);
    m_popup_2->setVisible(false);
    m_popup_3->setVisible(false);
}

void CharselectScene::onStart(SelectCharNo no)
{
    // 何度も押されないように一度押されたらアクションを無効にする
    this->getEventDispatcher()->removeAllEventListeners();
    
    // 0.5秒待ってからCallFuncを呼ぶ
    auto delay = DelayTime::create(0.2f);
    
    // ゲームを始めるアクション
    auto startGame = CallFunc::create([this, no]{
        // スタートボタン音SE再生
        AudioManager::getInstance()->playSe("ui_title_start");
        
        // ユーザーデータ作成
        PlayerValue::getInstance()->initialActivation();
        auto partyValue = PartyValue::getInstance();
        if(partyValue){
            partyValue->initialActivation();
            partyValue->setCharStorageParam(1, no, 5, 0);
            partyValue->setPartyValueParam(0, 1);
        }
        
        // クエスト選択画面へ移行
        auto transition = TransitionFade::create(0.5f, QuestScene::createScene(), Color3B::WHITE);
        Director::getInstance()->replaceScene(transition);
    });
    this->runAction(Sequence::create(delay, startGame, NULL));
}
