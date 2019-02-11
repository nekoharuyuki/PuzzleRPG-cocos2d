#ifndef __QUEST_SCENE_H__
#define __QUEST_SCENE_H__

#include "SceneData.h"

class QuestScene :
public SceneData,
public cocos2d::Layer
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
    
    static cocos2d::Scene* createScene();
    
    SCENE_CREATE_FUNC(QuestScene, "quest/QuestScene.csb")
    bool onCreate() override;
    
private:
    CC_SYNTHESIZE(int, m_questNo, QuestNo);                    //クエストの順番
    CC_SYNTHESIZE_READONLY(QuestType, m_questType, QuestType); //クエストの種類
    
    void onQuest();
    void onQuestStart();
    void onBack();
    
    Node* m_popup_quest;
};

#endif // __QUEST_SCENE_H__
