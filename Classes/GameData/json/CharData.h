#ifndef __CHAR_DATA__
#define __CHAR_DATA__

#include "cocos2d.h"

class CharData
{
private:
    CharData();   //コンストラクタ
    static CharData* m_instance;
    
    // キャラクター情報の設定リスト
    struct CharDataParams {
        std::string charName;
        int charId;
        int charHp;
        int charMaxHp;
        int charAtk;
        int charMaxAtk;
        int charAttribute;
        std::vector<int> charMaxLevel;
        int charRare;
        int charSkill;
        std::string charSkillText;
        int charSkillTurn;
        int charMixExp;
        int charLevel;
        int charExp;
        int charPrice;
        int charOverLimit;
        std::vector<int> charEvolution; 
    };
    static std::map<int, CharDataParams> m_charDataList;
    
    struct EnemyDataParams {
        std::string enemyName;
        int enemyHp;
        int enemyMaxHp;
        int enemyAtk;
        int enemyMaxAtk;
        int enemyAttribute;
        int enemyExp;
        int enemyTurn;
    };
    static std::map<int, EnemyDataParams> m_enemyDataList;
    
    // マップ管理ファイルのファイルパス
    CC_SYNTHESIZE(std::string, m_charListFile,  CharListFile);
    CC_SYNTHESIZE(std::string, m_enemyListFile, EnemyListFile);
    
public:
    ~CharData();
    static CharData* getInstance();
    static void deleteInstance();
    
    bool charDataJsonOpen(const std::string& filename);
    
    static CharDataParams getCharData(int dataId){ return m_charDataList[dataId]; }
    static EnemyDataParams getEnemyData(int dataId){ return m_enemyDataList[dataId]; }
};

#endif /* defined(__CHAR_DATA__) */
