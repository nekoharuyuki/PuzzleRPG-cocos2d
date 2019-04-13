//
//  PartyValue.cpp
//  PuzzleRPG
//
//  Created by neko on 2018/10/08.
//

#include "PartyValue.h"
#include "GameDataSQL.h"
#include "CharData.h"
#include "json/rapidjson.h"
#include "json/document.h"

#define MAX_MEMBER 3
#define MEMBER_LOOP_COUNT (MAX_MEMBER - 1)
#define MAX_LEVEL 100

PartyValue* PartyValue::m_instance = nullptr;
std::map<int, PartyValue::CharStorageParams> PartyValue::m_charStorageDataList;

//コンストラクタ
PartyValue::PartyValue()
: m_partyValue("")
, m_charStorage("")
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
    
    GameDataSQL::sqliteSetValueForKey("PartyValue", "");
    GameDataSQL::sqliteSetValueForKey("CharStorage", "");
}

void PartyValue::dataLoad()
{
    const char *partyValue = GameDataSQL::sqliteGetValueForKey("PartyValue");
    m_partyValue = partyValue;
    const char *charStorage = GameDataSQL::sqliteGetValueForKey("CharStorage");
    m_charStorage = charStorage;
}

void PartyValue::dataSave()
{
    GameDataSQL::sqliteUpdateValueForKey("PartyValue", m_partyValue.c_str());
    GameDataSQL::sqliteUpdateValueForKey("CharStorage", m_charStorage.c_str());
}

// パーティーのストレージ情報を保存する
void PartyValue::setPartyValueParam(int memberId, int storageId)
{
    m_partyValue = GameDataSQL::sqliteGetValueForKey("PartyValue");
    
    if(m_partyValue == ""){
        // 初期データを保存
        m_partyValue = "{ ""\"member_1\""" : [ {""\"storageid\""" : 0} ], ""\"member_2\""" : [ {""\"storageid\""" : 0} ], ""\"member_3\""" : [ {""\"storageid\""" : 0} ] }";
        GameDataSQL::sqliteUpdateValueForKey("PartyValue", m_partyValue.c_str());
    }
    
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(m_partyValue.c_str());
    
    if (doc.HasParseError()) {
        CCLOG("JSON ERROR.");
    }
    if(!doc.IsObject()) {
        CCLOG("invalid!");
    }
    
    std::map<int, int> memberData;
    for(int i = 0; i < MEMBER_LOOP_COUNT; i++ ){
        char buf[] = "";
        strcpy(buf, "member_");
        strcat(buf, std::to_string(i+1).c_str());
        const rapidjson::Value& list = doc[buf];
        for(rapidjson::SizeType j = 0; j < list.Size(); j++){
            memberData[i] = list[j]["storageid"].GetInt();
        }
    }
    
    switch (memberId) {
        case 0:
            m_partyValue = "{ ""\"member_1\""" : [ {""\"storageid\""" : " + std::to_string(storageId) + "} ], ""\"member_2\""" : [ {""\"storageid\""" : " + std::to_string(memberData[1]) + "} ], ""\"member_3\""" : [ {""\"storageid\""" : " + std::to_string(memberData[2]) + "} ] }";
            break;
        case 1:
            m_partyValue = "{ ""\"member_1\""" : [ {""\"storageid\""" : " + std::to_string(memberData[0]) + "} ], ""\"member_2\""" : [ {""\"storageid\""" : " + std::to_string(storageId) + "} ], ""\"member_3\""" : [ {""\"storageid\""" : " + std::to_string(memberData[2]) + "} ] }";
            break;
        case 2:
            m_partyValue = "{ ""\"member_1\""" : [ {""\"storageid\""" : " + std::to_string(memberData[0]) + "} ], ""\"member_2\""" : [ {""\"storageid\""" : " + std::to_string(memberData[1]) + "} ], ""\"member_3\""" : [ {""\"storageid\""" : " + std::to_string(storageId) + "} ] }";
            break;
        default:
            break;
    }
    //CCLOG("%s", m_partyValue.c_str());
    GameDataSQL::sqliteUpdateValueForKey("PartyValue", m_partyValue.c_str());
}

// パーティーのIDからキャラクターストレージのIDを取得する
int PartyValue::getPartyMemberForStorageId(int memberId)
{
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(m_partyValue.c_str());
    
    if (doc.HasParseError() || !doc.IsObject()) {
        // エラー
        CCLOG("JSON ERROR.");
    }
    
    char buf[] = "";
    strcpy(buf, "member_");
    strcat(buf, std::to_string(memberId+1).c_str());
    const rapidjson::Value& list = doc[buf];
    for(rapidjson::SizeType i = 0; i < list.Size(); i++){
        return list[i]["storageid"].GetInt();
    }
    return 0;
}

// キャラクターストレージの情報を整理して格納する
void PartyValue::setCharStorageParam(int storageId, int charId, int level, int exp)
{
    m_charStorage = GameDataSQL::sqliteGetValueForKey("CharStorage");
    
    if(m_charStorage == ""){
        // 初期データを保存
        m_charStorage = "{""\"storageId\""" : 0, ""\"charId\""" : 0, ""\"level\""" : 0, ""\"exp\""" : 0};";
        GameDataSQL::sqliteUpdateValueForKey("CharStorage", m_charStorage.c_str());
    }
    
    
    
    //CCLOG("%s", m_charStorage.c_str());
    GameDataSQL::sqliteUpdateValueForKey("CharStorage", m_charStorage.c_str());
}

// キャラクターストレージの情報からキャラクターのパラメータを取得する
std::string PartyValue::getCharStorageFromCharParam(int storageId)
{
    std::string charStorageParam = "";
    return charStorageParam;
}

int PartyValue::getTotalHp()
{
    int hp = 0;
    for(int i = 0; i < MEMBER_LOOP_COUNT; i++ ){
//        hp += partyValue[i].hp;
    }
    return hp;
}

int PartyValue::getAtk(int attribute)
{
    int atk = 0;
    for(int i = 0; i < MEMBER_LOOP_COUNT; i++){
//        if( attribute == partyValue[i].attribute ){
//            atk += partyValue[i].atk;
//        }
    }
    return atk;
}

int PartyValue::getTotalAtk()
{
    int atk = 0;
    for( int i = 0; i < MEMBER_LOOP_COUNT; i++ ){
//        atk += partyValue[i].atk;
    }
    return atk;
}

// 取得経験値のテーブル
int PartyValue::m_expTable[] =  {0,5,29,81,168,293,463,681,951,1277,1663,2110,2623,3204,3856,4582,5385,6266,7229,8275,9407,10628,11938,13342,14839,16434,18127,19921,21817,23817,25924,28139,30463,32899,35448,38113,40894,43793,46812,49953,53217,56606,60121,63764,67536,71439,75474,79643,83947,88388,92967,97685,102544,107546,112690,117980,123416,129000,134733,140616,146650,152837,159178,165674,172327,179138,186107,193237,200528,207982,215600,223383,231332,239448,247733,256187,264812,273609,282579,291724,301043,310539,320213,330065,340097,350309,360703,371281,382042,392988,404120,415439,426947,438643,450530,462608,474878,487342,500000};

bool PartyValue::levelUpCheck(int level, int exp)
{
    if( level < getLevel(exp) ){
        return true;
    }
    return false;
}

int PartyValue::getCurrentExp(int level, int exp)
{
    int currentExp =0;
    currentExp = exp - m_expTable[level-1];
    return currentExp;
}

int PartyValue::getNextExp(int level)
{
    int nextExp = 0;
    nextExp = m_expTable[level] - m_expTable[level-1];
    return nextExp;
}

int PartyValue::getLevel(int exp)
{
    int level = 0;
    for( int i = 0; i < MAX_LEVEL; i++ ){
        if( m_expTable[i] > exp ){
            level = i;
            break;
        }
    }
    return level;
}
