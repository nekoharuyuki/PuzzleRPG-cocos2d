//
//  BattleCharSprite.h
//  PuzzleRPG
//
//  Created by neko on 2018/06/10.
//

#ifndef BattleCharSprite_h
#define BattleCharSprite_h

#include "cocos2d.h"

class BattleCharSprite : public cocos2d::Sprite
{
public:
    BattleCharSprite(); //コンストラクタ
    
    //キャラクター属性
    enum class CharType
    {
        Member, // メンバー
        Enemy,  // 敵
    };
    
    static BattleCharSprite* create(int charId, CharType charType); //インスタンス生成
    virtual bool init(int charId, CharType charType); //初期化
    static std::string getSelectMemberCharImageFilePath(int charId);
    static std::string getSelectEnemyCharImageFilePath(int charId);
};

#endif /* BattleCharSprite_hpp */
