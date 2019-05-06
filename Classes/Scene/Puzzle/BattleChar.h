#ifndef __PuzzleGame__Character__
#define __PuzzleGame__Character__

#include "cocos2d.h"

class BattleChar : public cocos2d::Ref
{
public:
    BattleChar(); //コンストラクタ
    static BattleChar* create(); //インスタンス生成
    
    //キャラクター属性
    enum class Element
    {
        Fire   = 1,  //火
        Water  = 2,  //水
        Wind   = 3,  //風
        Holy   = 4,  //光
        Shadow = 5,  //闇
        None   = 0,  //なし
    };
    
    float getHpPercentage(); //ヒットポイント（％値）取得
    bool isAttackTurn(); //攻撃ターン（敵の場合）チェック
    static int getDamage(int ballCount, int chainCount, BattleChar* attacker, BattleChar* defender); //ダメージ数取得
    
protected:
    CC_SYNTHESIZE(int, m_remainingTurn, RemainingTurn); //攻撃するまでの残りターン
    CC_SYNTHESIZE(int, m_hp, Hp);                       //ヒットポイント
    CC_SYNTHESIZE(int, m_maxHp, MaxHp);                 //最大ヒットポイント
    CC_SYNTHESIZE(int, m_attack, Attack);               //攻撃力
    CC_SYNTHESIZE(Element, m_element, Element);         //属性
    CC_PROPERTY(int, m_turnCount, TurnCount);           //攻撃ターン数（敵の場合）
    
    static float getElementBonus(Element attackElement, Element defenseElement); //属性による攻撃ボーナス
};

#endif /* defined(__PuzzleGame__Character__) */
