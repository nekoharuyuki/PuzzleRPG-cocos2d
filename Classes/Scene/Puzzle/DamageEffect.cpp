//
//  DamageEffect.cpp
//  PuzzleRPG
//
//  Created by neko on 2018/12/25.
//

#include "DamageEffect.h"

using namespace std;
using namespace cocos2d;

DamageEffect::DamageEffect()
{
    // nop
}

void DamageEffect::createLabels(string dmg)
{
    for (int i = 0; i < dmg.length(); i++)
    {
        TTFConfig ttfConfig("fonts/babarageo3.ttf", 10, GlyphCollection::DYNAMIC);
        auto label = Label::createWithTTF(ttfConfig, std::string{ dmg[i] });
        label->setTag(i);
        this->addChild(label);
    }
}

void DamageEffect::setupCleanupAction(string dmg, float dulation)
{
    // エフェクトが全部終わったら自殺する設定
    Node* last = this->getChildByTag(dmg.length()-1);
    last->runAction(Sequence::create(DelayTime::create(dulation + 0.7f),
                                     CallFunc::create(CC_CALLBACK_0(DamageEffect::remove, this)), nullptr));
}

std::vector<Node*> DamageEffect::getLabels(string dmg)
{
    vector<Node*> labelList;
    for (int i = 0; i < dmg.length(); i++)
    {
        labelList.push_back(this->getChildByTag(i));
    }
    
    return labelList;
}

DamageEffect::~DamageEffect()
{
    this->remove();
}

bool DamageEffect::init()
{
    if (!Node::init()) {
        return false;
    }
    return true;
}

void DamageEffect::showEffect(int dmg)
{
    string dmgStr = to_string(dmg);
    
    this->createLabels(dmgStr);
    
    // 数字がジャンプする動作の設定
    int i = 0;
    float dulation = 0.0f;
    for (Node* _label : this->getLabels(dmgStr))
    {
        _label->setPosition(Vec2(i * 14, 0));
        
        auto dylayAction = DelayTime::create(i * 0.04);
        auto jumpAction1 = JumpBy::create(0.25f, Vec2(0, -10), 28, 1);
        auto jumpAction2 = JumpBy::create(0.1f, Vec2(0, 0), 12, 1);
        _label->runAction(Sequence::create(dylayAction, jumpAction1, jumpAction2, nullptr));
        
        i++;
    }
    
    this->setupCleanupAction(dmgStr, dulation);
}

void DamageEffect::remove()
{
    this->removeAllChildrenWithCleanup(true);
    this->removeFromParentAndCleanup(true);
}
