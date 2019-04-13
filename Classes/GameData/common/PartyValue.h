//
//  PartyValue.hpp
//  PuzzleRPG
//
//  Created by neko on 2018/10/08.
//

#ifndef PartyValue_h
#define PartyValue_h

#include "cocos2d.h"

class PartyValue
{
private:
    PartyValue(); //コンストラクタ
    static PartyValue* m_instance;
    
    static int m_expTable[];
    
    // 保有しているキャラクターのパラメーターリスト
    struct CharStorageParams {
        std::string charName;
        int charId;
        int charHp;
        int charAtk;
        int charAttribute;
        int charLevel;
        int charExp;
    };
    static std::map<int, CharStorageParams> m_charStorageDataList;
    
public:
    ~PartyValue();
    static PartyValue* getInstance();
    static void deleteInstance();
    
    void initialActivation();   // 初回起動時
    
    void dataLoad();
    void dataSave();
    
    void setPartyValueParam(int memberId, int storageId);
    int getPartyMemberForStorageId(int memberId);
    void setCharStorageParam(int storageId, int charId, int level, int exp);
    std::string getCharStorageFromCharParam(int storageId);
    
    int getTotalHp();
    int getAtk(int attribute);
    int getTotalAtk();
    
    bool levelUpCheck(int level, int exp);
    int getCurrentExp(int level, int exp);
    int getNextExp(int level);
    int getLevel(int exp);
    
    CC_SYNTHESIZE(std::string, m_partyValue, PartyValue);
    CC_SYNTHESIZE(std::string, m_charStorage, CharStorage);
};

#endif /* PartyValue_h */
