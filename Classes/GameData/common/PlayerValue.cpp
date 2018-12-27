//
//  PlayerValue.cpp
//  PuzzleRPG
//
//  Created by neko on 2018/10/08.
//

#include "PlayerValue.h"
#include "GameDataSQL.h"

PlayerValue* PlayerValue::m_instance = nullptr;

//コンストラクタ
PlayerValue::PlayerValue()
: m_coin(0)
, m_clearMap(0)
{
}

// デストラクタ
PlayerValue::~PlayerValue() {
    deleteInstance();
}

// 初期化
PlayerValue* PlayerValue::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new PlayerValue();
    }
    return m_instance;
}

// 削除する際に使用
void PlayerValue::deleteInstance() {
    CC_SAFE_DELETE(m_instance);
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
    GameDataSQL::sqliteSetValueForKey("SeOnOff", "1");
    GameDataSQL::sqliteSetValueForKey("BgmOnOff", "1");
    dataLoad();
}

void PlayerValue::dataLoad()
{
    const char *coin = GameDataSQL::sqliteGetValueForKey("Coin");
    m_coin = atoi(coin);
    const char *clearMap = GameDataSQL::sqliteGetValueForKey("ClearMap");
    m_clearMap = atoi(clearMap);
    
    const char *seOnOff = GameDataSQL::sqliteGetValueForKey("SeOnOff");
    m_seOnOff = atoi(seOnOff);
    const char *bgmOnOff = GameDataSQL::sqliteGetValueForKey("BgmOnOff");
    m_bgmOnOff = atoi(bgmOnOff);
}

void PlayerValue::dataSave()
{
    GameDataSQL::sqliteUpdateValueForKey("Coin", std::to_string(m_coin).c_str());
    GameDataSQL::sqliteUpdateValueForKey("ClearMap", std::to_string(m_clearMap).c_str());
    GameDataSQL::sqliteUpdateValueForKey("SeOnOff", std::to_string(m_seOnOff).c_str());
    GameDataSQL::sqliteUpdateValueForKey("BgmOnOff", std::to_string(m_bgmOnOff).c_str());
}
