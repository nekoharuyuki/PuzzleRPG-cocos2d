//
//  ModalLayer.cpp
//  Modal
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//
//

#include "ModalLayer.h"
#include "VisibleRect.h"
#include "testResource.h"

using namespace cocos2d;

#define kModalLayerPriority -1

ModalLayer::ModalLayer()
{
}

ModalLayer::~ModalLayer()
{
}

bool ModalLayer::init()
{
    if ( !Layer::init() ){ return false; }
    
    Rect visibleSize = VisibleRect::getVisibleRect();
    Sprite* frame = Sprite::create(s_modalFrame);
    frame->setPosition(visibleSize.size.width/2, visibleSize.size.height/2);
    this->addChild(frame);
    auto *pCloseItem = MenuItemImage::create(s_pathModalClose1, s_pathModalClose2, CC_CALLBACK_1(ModalLayer::menuCloseCallback, this));
    pCloseItem->setPosition(visibleSize.size.width/2+frame->getContentSize().width/2-pCloseItem->getContentSize().width/2-10,
                            visibleSize.size.height/2+frame->getContentSize().height/2-pCloseItem->getContentSize().height/2-10);
    auto pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition( Vec2::ZERO );
    this->addChild(pMenu);
    
    // モーダル処理
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch *touch,Event*event)->bool{
        return true;
    };
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

bool ModalLayer::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) {
    // can not touch on back layers    
    return true;
}

void ModalLayer::menuCloseCallback(cocos2d::Ref* pSender){
    this->removeFromParentAndCleanup(true);
}
