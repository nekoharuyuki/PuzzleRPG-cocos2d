//
//  CharIconSprite.hpp
//  PuzzleRPG
//
//  Created by neko on 2019/05/03.
//

#ifndef BattleCharIconSprite_h
#define BattleCharIconSprite_h

#include "cocos2d.h"

class BattleCharIconSprite : public cocos2d::Sprite
{
public:
    BattleCharIconSprite(); //コンストラクタ
    
    //キャラクター属性
    enum class CharType
    {
        Member, // メンバー
        Enemy,  // 敵
    };
    
    static BattleCharIconSprite* create(int charId, CharType charType); //インスタンス生成
    virtual bool init(int charId, CharType charType); //初期化
    static std::string getSelectMemberIconImageFilePath(int charId);
    static std::string getSelectEnemyIconImageFilePath(int charId);
};

#endif /* BattleCharIconSprite_h */
