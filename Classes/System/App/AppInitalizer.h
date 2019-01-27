//
//  AppInitalizer.h
//  PuzzleRPG
//
//  Created by neko on 2018/07/28.
//

#ifndef AppInitalizer_h
#define AppInitalizer_h

#include "cocos2d.h"

class AppInitalizer
{
public:
    
    // アプリ起動時の初期処理用のメソッド
    static void init();
    
    // This function will be called when the app is inactive. When comes a phone call,it's be invoked too
    // バックグラウンド移行後にコールされるメソッド
    static void applicationDidEnterBackground();
    
    // this function will be called when the app is active again
    // フォアグラウンド移行直前にコールされるメソッド
    static void applicationWillEnterForeground();
};

#endif /* AppInitalizer_h */
