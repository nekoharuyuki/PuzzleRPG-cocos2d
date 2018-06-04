#include "CharData.h"
#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;

CharData* CharData::m_instance = nullptr;
std::map<int, CharData::CharDataParams> CharData::m_charDataList;
std::map<int, CharData::EnemyDataParams> CharData::m_enemyDataList;

CharData::CharData()
: m_charListFile("")
, m_enemyListFile("")
{
}

// デストラクタ
CharData::~CharData() {
    
}

// 初期化
CharData* CharData::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new CharData();
    }
    return m_instance;
}

// 削除する際に使用
void CharData::deleteInstance() {
    if (m_instance != nullptr) {
        delete m_instance;
    }
    m_instance = nullptr;
}

bool CharData::charDataJsonOpen(const std::string& filename)
{
    // ファイル読み込み
    std::string strData = FileUtils::getInstance()->getStringFromFile(filename);
    
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(strData.c_str());
    
    if (doc.HasParseError()) {
        // 解析エラー
        CCLOG("JSON parse error.");
        return false;
    }
    
    if(!doc.IsObject()) {
        // パースエラーした状態でハンドリングせずにIsObject判定するとfalseになる
        CCLOG("invalid!");
        return false;
    }
    
    CCLOG("%s", strData.c_str());
    
    // 初期化
    m_charDataList.clear();
    
    // キーと値を変数に登録する
    const rapidjson::Value& charList = doc["char"];
    
    // キーと値をリストに登録する
    // キャラのデータ取得
    for(rapidjson::SizeType i = 0; i < charList.Size(); i++){
        m_charDataList[i].charName      = charList[i]["name"].GetString();
        m_charDataList[i].charId        = charList[i]["id"].GetInt();
        m_charDataList[i].charHp        = charList[i]["hp"].GetInt();
        m_charDataList[i].charMaxHp     = charList[i]["maxHp"].GetInt();
        m_charDataList[i].charAtk       = charList[i]["atk"].GetInt();
        m_charDataList[i].charMaxAtk    = charList[i]["maxAtk"].GetInt();
        m_charDataList[i].charAttribute = charList[i]["attribute"].GetInt();
        if (charList[i]["maxLevel"].IsArray()) {
            const rapidjson::Value& maxLevel = charList[i]["maxLevel"];
            rapidjson::SizeType num = maxLevel.Size();
            for(rapidjson::SizeType levelCount = 0; levelCount < num; levelCount++){
                m_charDataList[i].charMaxLevel.push_back(maxLevel[levelCount].GetInt());
            }
        }
        m_charDataList[i].charRare      = charList[i]["rare"].GetInt();
        m_charDataList[i].charSkill     = charList[i]["skill"].GetInt();
        m_charDataList[i].charSkillText = charList[i]["skillText"].GetString();
        m_charDataList[i].charSkillTurn = charList[i]["skillTurn"].GetInt();
        m_charDataList[i].charMixExp    = charList[i]["mix_exp"].GetInt();
        m_charDataList[i].charLevel     = charList[i]["level"].GetInt();
        m_charDataList[i].charExp       = charList[i]["exp"].GetInt();
        m_charDataList[i].charPrice     = charList[i]["price"].GetInt();
        m_charDataList[i].charOverLimit = charList[i]["overLimit"].GetInt();
        if (charList[i]["evolution"].IsArray()) {
            const rapidjson::Value& evolution = charList[i]["evolution"];
            rapidjson::SizeType num = evolution.Size();
            for(rapidjson::SizeType evolCount = 0; evolCount < num; evolCount++){
                m_charDataList[i].charEvolution.push_back(evolution[evolCount].GetInt());
            }
        }
    }
    
    // キーと値を変数に登録する
    const rapidjson::Value& enemyList = doc["enemy"];
    
    // キーと値をリストに登録する
    // 敵のデータ取得
    for(rapidjson::SizeType i = 0; i < enemyList.Size(); i++){
        m_enemyDataList[i].enemyName      = enemyList[i]["name"].GetString();
        m_enemyDataList[i].enemyHp        = enemyList[i]["hp"].GetInt();
        m_enemyDataList[i].enemyMaxHp     = enemyList[i]["maxHp"].GetInt();
        m_enemyDataList[i].enemyAtk       = enemyList[i]["atk"].GetInt();
        m_enemyDataList[i].enemyMaxAtk    = enemyList[i]["maxAtk"].GetInt();
        m_enemyDataList[i].enemyAttribute = enemyList[i]["attribute"].GetInt();
        m_enemyDataList[i].enemyExp       = enemyList[i]["exp"].GetInt();
        m_enemyDataList[i].enemyTurn      = enemyList[i]["turn"].GetInt();
    }
    
    // 現在のファイルをセット
    m_charListFile = filename;
    m_enemyListFile = filename;
    
    return true;
}
