#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

class TestController;

class TitleScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);
    
private:
    
    void titleSceneButtonPress(Node* rootNode);
    void startButtonPress(Node* rootNode);
    void mypageButtonPress(Node* rootNode);
    void otherButtonPress(Node* rootNode);
    void debugButtonPress(Node* rootNode);
    
    static cocos2d::Scene* m_titleScene;
    
#if COCOS2D_DEBUG
    TestController* m_projectController;
#endif
};

#endif // __TITLE_SCENE_H__
