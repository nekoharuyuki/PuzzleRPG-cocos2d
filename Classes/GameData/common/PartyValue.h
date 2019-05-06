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
    
public:
    ~PartyValue();
    static PartyValue* getInstance();
    static void deleteInstance();
    
    void initialActivation();   // 初回起動時
    
    void dataLoad();
    void dataSave();
    void sortCharStorage();
    
    void setPartyValueParam(int memberId, int storageId);
    int getPartyMemberForStorageId(int memberId);
    bool isPartyMembercharacter(int storageId);
    
    void setCharStorageParam(int storageId, int charId, int level, int exp);
    void newCharStorageParam(std::string newChar);
    int getCharStorageFromCharId(int storageId);
    int getCharStorageFromCharLevel(int storageId);
    int getCharStorageFromCharExp(int storageId);
    int getMaxStorageId();
    
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
