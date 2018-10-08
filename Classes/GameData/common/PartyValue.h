//
//  PartyValue.hpp
//  PuzzleRPG
//
//  Created by neko on 2018/10/08.
//

#ifndef PartyValue_h
#define PartyValue_h

class PartyValue : public cocos2d::Ref
{
public:
    PartyValue(); //コンストラクタ
    static PartyValue* create(); //インスタンス生成
    
    void initialActivation();   // 初回起動時
    
    void dataLoad();
    void dataSave();
    
    std::string getPartyCharId(int charId);
    std::string getPartyCharLv(int charId);
    
    int getTotalHp();
    
protected:
    
    // Party
    CC_SYNTHESIZE(int, m_partyChar1DataCharId, PartyChar1DataCharId);
    CC_SYNTHESIZE(int, m_partyChar1DataCharLv, PartyChar1DataCharLv);
    
    CC_SYNTHESIZE(int, m_partyChar2DataCharId, PartyChar2DataCharId);
    CC_SYNTHESIZE(int, m_partyChar2DataCharLv, PartyChar2DataCharLv);
    
    CC_SYNTHESIZE(int, m_partyChar3DataCharId, PartyChar3DataCharId);
    CC_SYNTHESIZE(int, m_partyChar3DataCharLv, PartyChar3DataCharLv);
};

#endif /* PartyValue_h */
