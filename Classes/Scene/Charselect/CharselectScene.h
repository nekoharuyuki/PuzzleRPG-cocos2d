//
//  CharselectScene.h
//  PuzzleRPG
//
//  Created by neko on 2018/03/25.
//

#ifndef CharselectScene_h
#define CharselectScene_h

#include "cocos2d.h"

class CharselectScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(CharselectScene);
    
private:
    enum SelectCharNo
    {
        SelectCharNo01 = 0,
        SelectCharNo02,
        SelectCharNo03,
    };
    
    void onChar( SelectCharNo no );
    void onYes();
    void onBack();
    void onStart();
    
    Node* m_popup_1;
    Node* m_popup_2;
    Node* m_popup_3;
};

#endif /* CharselectScene_h */
