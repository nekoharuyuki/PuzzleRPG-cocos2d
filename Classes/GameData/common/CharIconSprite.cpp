//
//  CharIconSprite.cpp
//  PuzzleRPG
//
//  Created by neko on 2019/05/03.
//

#include "CharIconSprite.h"

//コンストラクタ
CharIconSprite::CharIconSprite()
{
}

//インスタンス生成
CharIconSprite* CharIconSprite::create(int charId, CharType charType)
{
    CharIconSprite *pRet = new CharIconSprite();
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
bool CharIconSprite::init(int charId, CharType charType)
{
    switch (charType)
    {
        case CharType::MemberTypeA:
        {
            if (!Sprite::initWithFile(getSelectMemberIconImageTypeAFilePath(charId))){
                return false;
            }
            return true;
        }
        case CharType::Member:
        case CharType::MemberTypeB:
        {
            if (!Sprite::initWithFile(getSelectMemberIconImageTypeBFilePath(charId))){
                return false;
            }
            return true;
        }
        case CharType::Enemy:
        {
            if (!Sprite::initWithFile(getSelectEnemyIconImageFilePath(charId))){
                return false;
            }
            return true;
        }
        default: return false;
    }
}

//選択したキャラクターの画像を取得
std::string CharIconSprite::getSelectMemberIconImageTypeAFilePath(int charId)
{
    //選択したキャラクターに適した画像を返す
    switch (charId)
    {
        case 1:  return "asset/char/icon_chara_a_1.png";
        case 2:  return "asset/char/icon_chara_a_2.png";
        case 3:  return "asset/char/icon_chara_a_3.png";
        case 4:  return "asset/char/icon_chara_a_4.png";
        case 5:  return "asset/char/icon_chara_a_5.png";
        case 6:  return "asset/char/icon_chara_a_6.png";
        case 7:  return "asset/char/icon_chara_a_7.png";
        case 8:  return "asset/char/icon_chara_a_8.png";
        case 9:  return "asset/char/icon_chara_a_9.png";
        case 10: return "asset/char/icon_chara_a_10.png";
        case 11: return "asset/char/icon_chara_a_11.png";
        case 12: return "asset/char/icon_chara_a_12.png";
        default: return "asset/Default/Sprite.png";
    }
}
std::string CharIconSprite::getSelectMemberIconImageTypeBFilePath(int charId)
{
    //選択したキャラクターに適した画像を返す
    switch (charId)
    {
        case 1:  return "asset/char/icon_chara_b_1.png";
        case 2:  return "asset/char/icon_chara_b_2.png";
        case 3:  return "asset/char/icon_chara_b_3.png";
        case 4:  return "asset/char/icon_chara_b_4.png";
        case 5:  return "asset/char/icon_chara_b_5.png";
        case 6:  return "asset/char/icon_chara_b_6.png";
        case 7:  return "asset/char/icon_chara_b_7.png";
        case 8:  return "asset/char/icon_chara_b_8.png";
        case 9:  return "asset/char/icon_chara_b_9.png";
        case 10: return "asset/char/icon_chara_b_10.png";
        case 11: return "asset/char/icon_chara_b_11.png";
        case 12: return "asset/char/icon_chara_b_12.png";
        default: return "asset/Default/Sprite.png";
    }
}

//選択したキャラクターの画像を取得
std::string CharIconSprite::getSelectEnemyIconImageFilePath(int charId)
{
    //選択したキャラクターに適した画像を返す
    switch (charId)
    {
        case 1:  return "asset/char/enemy_1.png";
        case 2:  return "asset/char/enemy_2.png";
        case 3:  return "asset/char/enemy_3.png";
        case 4:  return "asset/char/enemy_4.png";
        case 5:  return "asset/char/enemy_5.png";
        case 6:  return "asset/char/enemy_6.png";
        case 7:  return "asset/char/enemy_7.png";
        case 8:  return "asset/char/enemy_8.png";
        case 9:  return "asset/char/enemy_9.png";
        default: return "asset/Default/Sprite.png";
    }
}
