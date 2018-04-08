//
//  CharSelectSprite.cpp
//  PuzzleRPG
//
//  Created by neko on 2018/04/08.
//

#include "CharSelectSprite.h"

USING_NS_CC;

//コンストラクタ
CharSelectSprite::CharSelectSprite()
{
}

//インスタンス生成
CharSelectSprite* CharSelectSprite::create(int charId)
{
    CharSelectSprite *pRet = new CharSelectSprite();
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
bool CharSelectSprite::init(int charId)
{
    if (!Sprite::initWithFile(getSelectCharImageFilePath(charId))){
        return false;
    }
    return true;
}

//選択したキャラクターの画像を取得
std::string CharSelectSprite::getSelectCharImageFilePath(int charId)
{
    //選択したキャラクターに適した画像を返す
    switch (charId)
    {
        case 0:    return "asset/char/chara_princessselect_1.png";
        case 1:    return "asset/char/chara_princessselect_2.png";
        case 2:    return "asset/char/chara_princessselect_3.png";
        default:   return "asset/Default/Sprite.png";
    }
}
