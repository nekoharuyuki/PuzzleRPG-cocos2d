//
//  CharSelectIconSprite.h
//  PuzzleRPG
//
//  Created by neko on 2018/04/10.
//

#ifndef CharSelectIconSprite_h
#define CharSelectIconSprite_h

#include "cocos2d.h"

class CharSelectIconSprite : public cocos2d::Sprite
{
public:
    CharSelectIconSprite(); //コンストラクタ
    static CharSelectIconSprite* create(int charId); //インスタンス生成
    virtual bool init(int charId); //初期化
    static std::string getSelectCharIconImageFilePath(int charId);
};

#endif /* CharSelectIconSprite_h */
