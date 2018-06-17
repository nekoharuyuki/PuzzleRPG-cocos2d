//
//  BattleCharSprite.cpp
//  PuzzleRPG
//
//  Created by neko on 2018/06/10.
//

#include "BattleCharSprite.h"

USING_NS_CC;

//コンストラクタ
BattleCharSprite::BattleCharSprite()
{
}

//インスタンス生成
BattleCharSprite* BattleCharSprite::create(int charId, CharType charType)
{
    BattleCharSprite *pRet = new BattleCharSprite();
    if (pRet && pRet->init(charId, charType)){
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

//初期化
bool BattleCharSprite::init(int charId, CharType charType)
{
    switch (charType)
    {
        case CharType::Member:
        {
            if (!Sprite::initWithFile(getSelectMemberCharImageFilePath(charId))){
                return false;
            }
            return true;
        }
        case CharType::Enemy:
        {
            if (!Sprite::initWithFile(getSelectEnemyCharImageFilePath(charId))){
                return false;
            }
            return true;
        }
        default: return false;
    }
}

//選択したキャラクターの画像を取得
std::string BattleCharSprite::getSelectMemberCharImageFilePath(int charId)
{
    //選択したキャラクターに適した画像を返す
    switch (charId)
    {
        case 1:  return "asset/char/chara_player_1.png";
        case 2:  return "asset/char/chara_player_2.png";
        case 3:  return "asset/char/chara_player_3.png";
        case 4:  return "asset/char/chara_player_4.png";
        case 5:  return "asset/char/chara_player_5.png";
        case 6:  return "asset/char/chara_player_6.png";
        case 7:  return "asset/char/chara_player_7.png";
        case 8:  return "asset/char/chara_player_8.png";
        case 9:  return "asset/char/chara_player_9.png";
        case 10: return "asset/char/chara_player_10.png";
        case 11: return "asset/char/chara_player_11.png";
        case 12: return "asset/char/chara_player_12.png";
        default: return "asset/Default/Sprite.png";
    }
}

//選択したキャラクターの画像を取得
std::string BattleCharSprite::getSelectEnemyCharImageFilePath(int charId)
{
    //選択したキャラクターに適した画像を返す
    switch (charId)
    {
        case 1:  return "asset/char/chara_enemy_1.png";
        case 2:  return "asset/char/chara_enemy_2.png";
        case 3:  return "asset/char/chara_enemy_3.png";
        case 4:  return "asset/char/chara_enemy_4.png";
        case 5:  return "asset/char/chara_enemy_5.png";
        case 6:  return "asset/char/chara_enemy_6.png";
        case 7:  return "asset/char/chara_enemy_7.png";
        case 8:  return "asset/char/chara_enemy_8.png";
        case 9:  return "asset/char/chara_enemy_9.png";
        default: return "asset/Default/Sprite.png";
    }
}
