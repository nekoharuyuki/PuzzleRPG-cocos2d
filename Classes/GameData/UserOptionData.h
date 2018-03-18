//
//  UserOptionData.h
//  PuzzleRPG
//
//  Created by neko on 2018/03/18.
//

#ifndef UserOptionData_h
#define UserOptionData_h

#include "cocos2d.h"

class UserOptionData : public cocos2d::Node {
public:
    virtual  bool init();
    
    static void saveInt(const char *key,int value);
    static void saveString(const char *key,const cocos2d::__String *string);
    static void saveBool(const char *key,bool _bolean);
    
    static int loadInt(const char *key);
    static std::string loadString(const char *key);
    static bool loadBool(const char *key);
};

#endif /* UserOptionData_h */
