//
//  CharSelectIconSprite.cpp
//  PuzzleRPG
//
//  Created by neko on 2018/04/10.
//

#include "CharSelectIconSprite.h"

USING_NS_CC;

//コンストラクタ
CharSelectIconSprite::CharSelectIconSprite()
{
}

//インスタンス生成
CharSelectIconSprite* CharSelectIconSprite::create(int charId)
{
    CharSelectIconSprite *pRet = new CharSelectIconSprite();
    if (pRet && pRet->init(charId)){
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
bool CharSelectIconSprite::init(int charId)
{
    if (!Sprite::initWithFile(getSelectCharIconImageFilePath(charId))){
        return false;
    }
    return true;
}

//選択したキャラクターの画像を取得
std::string CharSelectIconSprite::getSelectCharIconImageFilePath(int charId)
{
    //選択したキャラクターに適した画像を返す
    switch (charId)
    {
        case 0:    return "asset/char/icon_chara_a_1.png";
        case 1:    return "asset/char/icon_chara_a_2.png";
        case 2:    return "asset/char/icon_chara_a_3.png";
        default:   return "asset/Default/Sprite.png";
    }
}
