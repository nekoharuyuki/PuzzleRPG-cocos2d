//
//  AppPlatform.mm
//  PuzzleRPG
//
//  Created by neko on 2019/02/09.
//

#include "AppPlatform.h"

using namespace cocos2d;

// アプリーケーションバージョンの取得
const char* AppPlatform::getAppVersion()
{
    NSDictionary *info = [[NSBundle mainBundle] infoDictionary];
    NSString *version = [info objectForKey:@"CFBundleVersion"];
    if (version) {
        __String* ret = __String::create([version UTF8String]);
        return ret->getCString();
    }
    return NULL;
}

AppPlatform* AppPlatform::instance = NULL;

AppPlatform* AppPlatform::sharedInstance()
{
    if (instance == NULL)
    {
        instance = new AppPlatform();
        instance->m_appkeydelegate = NULL;
    }
    return instance;
}
