//
//  CharSelectSprite.h
//  PuzzleRPG
//
//  Created by neko on 2018/04/08.
//

#ifndef CharSelectSprite_h
#define CharSelectSprite_h

#include "cocos2d.h"

class CharSelectSprite : public cocos2d::Sprite
{
public:
    CharSelectSprite(); //コンストラクタ
    static CharSelectSprite* create(int charId); //インスタンス生成
    virtual bool init(int charId); //初期化
    static std::string getSelectCharImageFilePath(int charId);
};

#endif /* CharSelectSprite_h */
