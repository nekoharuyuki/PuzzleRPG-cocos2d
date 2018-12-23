//
//  PlayerValue.h
//  PuzzleRPG
//
//  Created by neko on 2018/10/08.
//

#ifndef PlayerValue_h
#define PlayerValue_h

#include "cocos2d.h"

class PlayerValue
{
private:
    PlayerValue(); //コンストラクタ
    static PlayerValue* m_instance;
    
public:
    ~PlayerValue();
    static PlayerValue* getInstance();
    static void deleteInstance();
    
    void initialActivation();   // 初回起動時
    
    void dataLoad();
    void dataSave();
    
    CC_SYNTHESIZE(int, m_coin, Coin);           //ユーザーが保有しているコイン
    CC_SYNTHESIZE(int, m_clearMap, ClearMap);   //ユーザーがクリアしているマップ
};

#endif /* PlayerValue_h */
