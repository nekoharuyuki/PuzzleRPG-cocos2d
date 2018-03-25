#include "CharData.h"
#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;

CharData* CharData::m_instance = nullptr;
std::map<int, CharData::CharDataParams> CharData::m_charDataList;

CharData::CharData()
: m_charListFile("")
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
    const rapidjson::Value& mapList = doc["map"];
    // キーと値をリストに登録する
    for(rapidjson::SizeType i = 0; i < mapList.Size(); i++){
        /*
        m_charDataList[i].mapId       = mapList[i]["id"].GetInt();
        m_charDataList[i].mapName     = mapList[i]["name"].GetString();
        m_charDataList[i].mapStamina  = mapList[i]["stamina"].GetInt();
        m_charDataList[i].mapStage    = mapList[i]["stage"].GetInt();
        m_mapDam_charDataListtaList[i].mapDropCoin = mapList[i]["dropCoin"].GetInt();
        m_charDataList[i].mapBoss     = mapList[i]["boss"].GetBool();
         */
    }
    
    // 現在のファイルをセット
    m_charListFile = filename;
    
    return true;
}
