//
//  PlayerValue.cpp
//  PuzzleRPG
//
//  Created by neko on 2018/10/08.
//

#include "PlayerValue.h"
#include "GameDataSQL.h"

//コンストラクタ
PlayerValue::PlayerValue()
: m_coin(0)
, m_clearMap(0)
{
}

//インスタンス生成
PlayerValue* PlayerValue::create()
{
    PlayerValue *pRet = new PlayerValue();
    pRet->autorelease();
    
    return pRet;
}

// 初回起動時
void PlayerValue::initialActivation()
{
    // ローカルDBデータの有無を確認
    if(!GameDataSQL::hasData()){
        // 初回起動時にローカルDBデータを作成する
        GameDataSQL::sqliteCreateTable();
    }
    
    GameDataSQL::sqliteSetValueForKey("Coin", "100");
    GameDataSQL::sqliteSetValueForKey("ClearMap", "0");
    dataLoad();
}

void PlayerValue::dataLoad()
{
    const char *coin = GameDataSQL::sqliteGetValueForKey("Coin");
    m_coin = atoi(coin);
    const char *clearMap = GameDataSQL::sqliteGetValueForKey("ClearMap");
    m_clearMap = atoi(clearMap);
}

void PlayerValue::dataSave()
{
    GameDataSQL::sqliteUpdateValueForKey("Coin", std::to_string(m_coin).c_str());
    GameDataSQL::sqliteUpdateValueForKey("ClearMap", std::to_string(m_clearMap).c_str());
}
