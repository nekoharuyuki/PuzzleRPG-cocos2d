//
//  UserOptionData.cpp
//  PuzzleRPG
//
//  Created by neko on 2018/03/18.
//

#include "UserOptionData.h"

USING_NS_CC;

bool UserOptionData::init(){
    if (!Node::init()) {
        return false;
    }
    return false;
}

//char
void UserOptionData::saveInt(const char *key,int value){
    UserDefault *userDefalt = UserDefault::getInstance();
    userDefalt->setIntegerForKey(key, value);
    userDefalt ->flush();
}

void UserOptionData::saveString(const char *key,const __String *string){
    std::string hoge = string->_string;
    UserDefault *userDefalt = UserDefault::getInstance();
    userDefalt->setStringForKey(key, hoge);
    userDefalt ->flush();
}

void UserOptionData::saveBool(const char *key,bool _bolean){
    UserDefault *userDefalt = UserDefault::getInstance();
    userDefalt->setBoolForKey(key, _bolean);
    userDefalt ->flush();
}

#pragma mark -
#pragma mark ロード
int UserOptionData::loadInt(const char *key){
    UserDefault *userDefalt = UserDefault::getInstance();
    int _intvalue = userDefalt->getIntegerForKey(key);
    return _intvalue;
}

std::string UserOptionData::loadString(const char *key){
    UserDefault *userDefalt = UserDefault::getInstance();
    std::string string = userDefalt->getStringForKey(key);
    return string;
}

bool UserOptionData::loadBool(const char *key){
    UserDefault *userDefalt = UserDefault::getInstance();
    bool _boolean = userDefalt->getBoolForKey(key);
    return _boolean;
}
