//
//  CharselectScene.h
//  PuzzleRPG
//
//  Created by neko on 2018/03/25.
//

#ifndef CharselectScene_h
#define CharselectScene_h

#include "SceneData.h"

class CharselectScene :
public SceneData,
public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    SCENE_CREATE_FUNC(CharselectScene, "charselect/CharselectScene.csb")
    bool onCreate() override;
    
private:
    enum SelectCharNo
    {
        SelectCharNo01 = 0, // メイ[火]
        SelectCharNo02 = 1, // メイ[水]
        SelectCharNo03 = 2, // メイ[木]
    };
    
    void onChar(SelectCharNo no);
    void onYes(SelectCharNo no);
    void onBack();
    void onStart(SelectCharNo no);
    
    Node* m_popup_1;    // キャラクター選択ポップアップ
    Node* m_popup_2;    // キャラクター確認ポップアップ
    Node* m_popup_3;    // キャラクター決定ポップアップ
};

#endif /* CharselectScene_h */
