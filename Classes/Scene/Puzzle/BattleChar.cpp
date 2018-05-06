#include "BattleChar.h"

USING_NS_CC;

//コンストラクタ
BattleChar::BattleChar()
: m_hp(0)
, m_maxHp(0)
, m_attack(0)
, m_element(Element::None)
, m_turnCount(0)
, m_remainingTurn(0)
{
}

//インスタンス生成
BattleChar* BattleChar::create()
{
    BattleChar *pRet = new BattleChar();
    pRet->autorelease();
    
    return pRet;
}

//攻撃ターン数取得
int BattleChar::getTurnCount() const
{
    return m_turnCount;
}

//攻撃ターン数設定
void BattleChar::setTurnCount(int turnCount)
{
    m_turnCount = turnCount;
    m_remainingTurn = m_turnCount;
}

//ヒットポイント（％値）取得
float BattleChar::getHpPercentage()
{
    return m_hp * 100.f / m_maxHp;
}

//攻撃ターン（敵の場合）チェック
bool BattleChar::isAttackTurn()
{
    // 残りターンの計算
    m_remainingTurn--;
    
    if (m_remainingTurn <= 0)
    {
        // 残りターン数が0の場合、攻撃を行う
        m_remainingTurn = m_turnCount;
        return true;
    }
    
    return false;
}

//ダメージ数取得
int BattleChar::getDamage(int ballCount, int chainCount, BattleChar* attacker, BattleChar* defender)
{
    // 消したボールの個数によるダメージ
    float baseDamage = ballCount / 3.0 * 100;
    
    // 連鎖ボーナス
    float chainBonus = powf(1.1, chainCount - 1);
    
    // 属性ボーナス
    float elementBonus = getElementBonus(attacker->getElement(), defender->getElement());
    
    // ダメージにボーナスを乗算したものを返す
    return baseDamage * chainBonus * elementBonus;
}

//属性による攻撃ボーナス
float BattleChar::getElementBonus(Element attackElement, Element defenseElement)
{
    //攻撃属性
    switch (attackElement)
    {
        case Element::Fire:
        {
            //防御属性
            switch (defenseElement)
            {
                case Element::Wind:return 2;
                case Element::Water:return 0.5;
                default:return 1;
            }
            break;
        }
        case Element::Water:
        {
            //防御属性
            switch (defenseElement)
            {
                case Element::Fire:return 2;
                case Element::Wind:return 0.5;
                default:return 1;
            }
            break;
        }
        case Element::Wind:
        {
            //防御属性
            switch (defenseElement)
            {
                case Element::Water:return 2;
                case Element::Wind:return 0.5;
                default:return 1;
            }
            break;
        }
        case Element::Holy:
        {
            //防御属性
            switch (defenseElement)
            {
                case Element::Shadow:return 2;
                default:return 1;
            }
            break;
        }
        case Element::Shadow:
        {
            //防御属性
            switch (defenseElement)
            {
                case Element::Holy:return 2;
                default:return 1;
            }
            break;
        }
        default:
        {
            return 1;
        }
    }
}
