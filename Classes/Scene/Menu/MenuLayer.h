#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "cocos2d.h"

class MenuLayer : public cocos2d::Layer
{
protected:
    //Zオーダー
    enum ZOrder
    {
        BgForCharacter = 0,
        Level,
        Result,
    };
    
    enum Menu
    {
        ui_mypage_btn = 0,
        ui_quest_btn,
        ui_party_btn,
        ui_mix_btn,
        ui_shinka_btn,
        ui_etc_btn,
    };
    
public:
    virtual bool init();
    
    CREATE_FUNC(MenuLayer);
    
    bool uiButtonPushLoadMypageScene(Node* node);
    bool uiButtonPushLoadQuestScene(Node* node);
    bool uiButtonPushLoadPartyScene(Node* node);
    bool uiButtonPushLoadMixScene(Node* node);
    bool uiButtonPushLoadShinkaScene(Node* node);
    bool uiButtonPushLoadOtherScene(Node* node);
    
    bool uiButtonPushLoadScene(Node* node, Menu menu, const std::string& name);
    cocos2d::Scene* loadScene(Menu menu);
};

#endif // __MENU_LAYER_H__
