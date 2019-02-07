//
//  SceneData.h
//  PuzzleRPG
//
//  Created by neko on 2019/02/02.
//

#ifndef SceneData_h
#define SceneData_h

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

/*
 csbファイルからシーン作成のcreate関数メソッド
 */
#define SCENE_CREATE_FUNC(__TYPE__, __FN__)            \
    CREATE_FUNC(__TYPE__);                             \
public:                                                \
    static const char* getFileName(){ return __FN__; } \
private:                                               \
    virtual bool init() override                       \
    {                                                  \
        m_layer = this;                                \
        m_fileName = __FN__;                           \
        m_sceneName = #__TYPE__;                       \
        return onCreate();                             \
    }

class SceneDataHandler
{
public:
    virtual cocos2d::Node* loaded() = 0;
    
    const std::string& getFileName() const { return m_fileName; }
    const std::string& getSceneName() const { return m_sceneName; }
    cocos2d::Layer* getLayer() const { return m_layer; }
protected:
    cocos2d::Layer* m_layer = nullptr;
    std::string m_fileName;
    std::string m_sceneName;
};

class SceneData : public SceneDataHandler
{
protected:
    SceneData() {}
    virtual ~SceneData() {}
    
    virtual bool onCreate() { return true; }
    cocos2d::Node* loaded() override;
    cocos2d::Node* buildAndAddRoot();
    
private:
    cocos2d::Node* m_node = nullptr;
};

#endif /* SceneData_h */
