//
//  DamageEffect.hpp
//  PuzzleRPG
//
//  Created by neko on 2018/12/25.
//

#ifndef DamageEffect_hpp
#define DamageEffect_hpp

#pragma once
#pragma execution_character_set("utf-8")

#include "cocos2d.h"

// ダメージ表示を表します。
class DamageEffect : public cocos2d::Node
{
    DamageEffect();
    
    // 各桁を表すラベルを作成する
    void createLabels(std::string dmg);
    
    // 最後に自殺する動作を設定する
    void setupCleanupAction(std::string dmg, float dulation);
    
    // 生成したラベルを取り出す
    std::vector<Node*> getLabels(std::string dmg);
    
public:
    
    // リソースを解放してオブジェクトを破棄する
    ~DamageEffect();
    
    virtual bool init() override;
    CREATE_FUNC(DamageEffect);
    
    // 指定した数値でダメージエフェクトを開始する
    void showEffect(int dmg);
    
    // 全てのActionが終了した時の処理
    void remove();
};

#endif /* DamageEffect_hpp */
