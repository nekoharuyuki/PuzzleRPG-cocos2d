//
//  PartyValue.cpp
//  PuzzleRPG
//
//  Created by neko on 2018/10/08.
//

#include "PartyValue.h"
#include "GameDataSQL.h"

PartyValue* PartyValue::m_instance = nullptr;

//コンストラクタ
PartyValue::PartyValue()
: m_partyChar1DataCharId(0)
, m_partyChar1DataCharLv(0)
, m_partyChar2DataCharId(0)
, m_partyChar2DataCharLv(0)
, m_partyChar3DataCharId(0)
, m_partyChar3DataCharLv(0)
{
}

// デストラクタ
PartyValue::~PartyValue() {
    deleteInstance();
}

// 初期化
PartyValue* PartyValue::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new PartyValue();
    }
    return m_instance;
}

// 削除する際に使用
void PartyValue::deleteInstance() {
    CC_SAFE_DELETE(m_instance);
}

// 初回起動時
void PartyValue::initialActivation()
{
    // ローカルDBデータの有無を確認
    if(!GameDataSQL::hasData()){
        // 初回起動時にローカルDBデータを作成する
        GameDataSQL::sqliteCreateTable();
    }
    
    GameDataSQL::sqliteSetValueForKey("PartyChar1DataCharId", "");
    GameDataSQL::sqliteSetValueForKey("PartyChar1DataCharLv", "");
    
    GameDataSQL::sqliteSetValueForKey("PartyChar2DataCharId", "");
    GameDataSQL::sqliteSetValueForKey("PartyChar2DataCharLv", "");
    
    GameDataSQL::sqliteSetValueForKey("PartyChar3DataCharId", "");
    GameDataSQL::sqliteSetValueForKey("PartyChar3DataCharLv", "");
}

void PartyValue::dataLoad()
{
    const char *partyChar1DataCharId = GameDataSQL::sqliteGetValueForKey("PartyChar1DataCharId");
    m_partyChar1DataCharId = atoi(partyChar1DataCharId);
    const char *partyChar1DataCharLv = GameDataSQL::sqliteGetValueForKey("PartyChar1DataCharLv");
    m_partyChar1DataCharLv = atoi(partyChar1DataCharLv);
    
    const char *partyChar2DataCharId = GameDataSQL::sqliteGetValueForKey("PartyChar2DataCharId");
    m_partyChar2DataCharId = atoi(partyChar2DataCharId);
    const char *partyChar2DataCharLv = GameDataSQL::sqliteGetValueForKey("PartyChar2DataCharLv");
    m_partyChar2DataCharLv = atoi(partyChar2DataCharLv);
    
    const char *partyChar3DataCharId = GameDataSQL::sqliteGetValueForKey("PartyChar3DataCharId");
    m_partyChar3DataCharId = atoi(partyChar3DataCharId);
    const char *partyChar3DataCharLv = GameDataSQL::sqliteGetValueForKey("PartyChar3DataCharLv");
    m_partyChar3DataCharLv = atoi(partyChar3DataCharLv);
}

void PartyValue::dataSave()
{
    GameDataSQL::sqliteUpdateValueForKey("PartyChar1DataCharId", std::to_string(m_partyChar1DataCharId).c_str());
    GameDataSQL::sqliteUpdateValueForKey("PartyChar1DataCharLv", std::to_string(m_partyChar1DataCharLv).c_str());
    
    GameDataSQL::sqliteUpdateValueForKey("PartyChar2DataCharId", std::to_string(m_partyChar2DataCharId).c_str());
    GameDataSQL::sqliteUpdateValueForKey("PartyChar2DataCharLv", std::to_string(m_partyChar2DataCharLv).c_str());
    
    GameDataSQL::sqliteUpdateValueForKey("PartyChar3DataCharId", std::to_string(m_partyChar3DataCharId).c_str());
    GameDataSQL::sqliteUpdateValueForKey("PartyChar3DataCharLv", std::to_string(m_partyChar3DataCharLv).c_str());
}

std::string PartyValue::getPartyCharId(int charId)
{
    switch (charId)
    {
        case 0:    return std::to_string(m_partyChar1DataCharId).c_str();
        case 1:    return std::to_string(m_partyChar2DataCharId).c_str();
        case 2:    return std::to_string(m_partyChar3DataCharId).c_str();
        default:   return "";
    }
}

std::string PartyValue::getPartyCharLv(int charId)
{
    switch (charId)
    {
        case 0:    return std::to_string(m_partyChar1DataCharLv).c_str();
        case 1:    return std::to_string(m_partyChar2DataCharLv).c_str();
        case 2:    return std::to_string(m_partyChar3DataCharLv).c_str();
        default:   return "";
    }
}

int PartyValue::getTotalHp()
{
    int hp = 0;
    
    return hp;
}
