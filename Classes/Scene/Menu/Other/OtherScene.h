#ifndef __OTHER_SCENE_H__
#define __OTHER_SCENE_H__

#include "SceneData.h"

class OtherScene :
public SceneData,
public cocos2d::Layer
{
public:
    enum transition
    {
        transition_title = 0,
        transition_menu,
        transition_quest,
    };
    static transition m_transitionScene;
    
    OtherScene(); //コンストラクタ
    static cocos2d::Scene* createScene(transition scene);
    
    SCENE_CREATE_FUNC(OtherScene, "other/OtherScene.csb")
    bool onCreate() override;
    
    static bool getBgmStatus(){ return m_bgm; }
    static void setBgmStatus(bool status){ m_bgm = status; }
    static bool getSeStatus(){ return m_se; }
    static void setSeStatus(bool status){ m_se = status; }
    
private:
    
    static bool m_bgm;
    static bool m_se;
    
    void onBgmOnOff(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    void onSeOnOff(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    
    CC_SYNTHESIZE(cocos2d::ui::Button*, m_seOn,   seOn  );
    CC_SYNTHESIZE(cocos2d::ui::Button*, m_seOff,  seOff );
    CC_SYNTHESIZE(cocos2d::ui::Button*, m_bgmOn,  bgmOn );
    CC_SYNTHESIZE(cocos2d::ui::Button*, m_bgmOff, bgmOff);
};

#endif // __OTHER_SCENE_H__
