//
//  AppPlatform.h
//  PuzzleRPG
//
//  Created by neko on 2019/02/09.
//

#ifndef __AppPlatform__
#define __AppPlatform__

#include "cocos2d.h"

// キーイベント
class AppKeyDelegate
{
public:
    virtual void onAppKeyEvent(int keycode){};
};

class AppPlatform
{
private:
    static AppPlatform *instance;
public:
    static AppPlatform* sharedInstance();

    // アプリーケーションバージョンの取得
    static const char* getAppVersion();

    // キーイベント
    CC_SYNTHESIZE(AppKeyDelegate*, m_appkeydelegate, AppKeyDelegate);
};

#endif /* defined(__AppPlatform__) */
