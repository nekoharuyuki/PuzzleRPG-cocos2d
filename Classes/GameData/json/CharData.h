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
        int charHp;
        int charMaxHp;
        int charAtk;
        int charMaxAtk;
        int charAttribute;
        int charExp;
        int charTurn;
    };
    static std::map<int, CharDataParams> m_charDataList;
    
    // マップ管理ファイルのファイルパス
    CC_SYNTHESIZE(std::string, m_charListFile, CharListFile);
    
public:
    ~CharData();
    static CharData* getInstance();
    static void deleteInstance();
    
    bool charDataJsonOpen(const std::string& filename);
};

#endif /* defined(__CHAR_DATA__) */
