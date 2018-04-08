#ifndef __QUEST_SCENE_H__
#define __QUEST_SCENE_H__

#include "cocos2d.h"

class QuestScene : public cocos2d::Layer
{
protected:
    //クエストの種類
    enum class QuestType
    {
        Blue,   //青
        Red,    //赤
    };
    
    void initQuestmas(Node* node); //クエストマスの初期化
    
public:
    QuestScene();   //コンストラクタ
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(QuestScene);
    
private:
    CC_SYNTHESIZE(int, m_questNo, QuestNo);                    //クエストの順番
    CC_SYNTHESIZE_READONLY(QuestType, m_questType, QuestType); //クエストの種類
    
    void onQuest();
    void onQuestStart();
    void onBack();
    
    Node* m_popup_quest;
};

#endif // __QUEST_SCENE_H__
