//
//  AppInitalizer.cpp
//  PuzzleRPG
//
//  Created by neko on 2018/07/28.
//

#include "AppInitalizer.h"
#include "AudioManager.h"
#include "MapData.h"
#include "CharData.h"
#include "TitleScene.h"

#ifdef __USE_FIREBASE__
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "firebase/app.h"
#include "firebase/admob.h"
#include "FirebaseHelper.h"
#endif
#endif // __USE_FIREBASE__

USING_NS_CC;

/*!
 アプリ起動時の初期処理用のメソッド
 */
void AppInitalizer::init()
{
#ifdef __USE_FIREBASE__
    // Firebaseの初期化
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // Initialize Firebase for Android.
    firebase::App* app = firebase::App::Create(firebase::AppOptions(),
                                               JniHelper::getEnv(),
                                               JniHelper::getActivity());
    // Initialize AdMob.
    firebase::admob::Initialize(*app, "INSERT_YOUR_ADMOB_ANDROID_APP_ID");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    // Initialize Firebase for iOS.
    firebase::App* app = firebase::App::Create(firebase::AppOptions());
    // Initialize AdMob.
    firebase::admob::Initialize(*app, "INSERT_YOUR_ADMOB_IOS_APP_ID");
#endif
#endif // __USE_FIREBASE__
    
    // オーディオ定義ファイルの読み込み
    AudioManager::getInstance()->readAudioListFile("master/audioData.json");
    
    // クエストマップ定義ファイルの読み込み
    MapData::getInstance()->mapDataJsonOpen("master/mapData.json");
    
    // キャラクター定義ファイルの読み込み
    CharData::getInstance()->charDataJsonOpen("master/charData.json");
    
    FileUtils::getInstance()->addSearchPath("res");
    
    auto scene = TitleScene::createScene();
    auto director = Director::getInstance();
    if(director){
        director->runWithScene(scene);
    }
}

/*!
 バックグラウンド移行後にコールされるメソッド
 */
void AppInitalizer::applicationDidEnterBackground()
{
    // if you use SimpleAudioEngine, it must be pause
    //SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

/*!
 フォアグラウンド移行直前にコールされるメソッド
 */
void AppInitalizer::applicationWillEnterForeground()
{
    // if you use SimpleAudioEngine, it must resume here
    //SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
