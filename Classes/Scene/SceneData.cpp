//
//  SceneData.cpp
//  PuzzleRPG
//
//  Created by neko on 2019/02/02.
//

#include "SceneData.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Node* SceneData::loaded()
{
    if(buildAndAddRoot() == nullptr){
        return nullptr;
    }
    CCLOG("SceneData( %s )", m_sceneName.c_str());
    return m_node;
}

Node* SceneData::buildAndAddRoot()
{
    if(m_node != nullptr){
        return m_node;
    }
    if(m_layer == nullptr || m_fileName.empty()){
        return nullptr;
    }
    m_node = CSLoader::createNode(m_fileName);
    if(m_node == nullptr){
        return nullptr;
    }
    m_layer->addChild(m_node);
    
    return m_node;
}
