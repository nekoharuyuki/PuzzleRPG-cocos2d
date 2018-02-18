//
//  ModalScene.h
//  Modal
//
//  Created by Akihiro Matsuura on 5/22/13.
//  Copyright 2013 Syuhari, Inc. All rights reserved.
//
//

#ifndef __Modal__ModalScene__
#define __Modal__ModalScene__

#include "cocos2d.h"

class ModalLayer : public cocos2d::Layer
{
protected:
    ModalLayer();
    virtual ~ModalLayer();
    virtual bool init() override;
    
public:
    void menuCloseCallback(cocos2d::Ref* pSender);
    virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) override;
    CREATE_FUNC(ModalLayer);
};

#endif /* defined(__Modal__ModalScene__) */
