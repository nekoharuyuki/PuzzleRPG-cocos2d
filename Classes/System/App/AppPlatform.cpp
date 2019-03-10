//
//  AppPlatform.cpp
//  PuzzleRPG
//
//  Created by neko on 2019/02/09.
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "AppPlatform.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
// getAppVersionInJavaを定義しているactivityを指定する
#define CLASS_NAME "org/cocos2dx/cpp/AppActivity"
USING_NS_CC;

const char* AppPlatform::getAppVersion()
{
    JniMethodInfo t;
    const char* ret = NULL;
    
    if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getAppVersionInJava", "()Ljava/lang/String;")) {
        jstring jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
        std::string sstr = JniHelper::jstring2string(jstr);
        
        t.env->DeleteLocalRef(t.classID);
        t.env->DeleteLocalRef(jstr);
        
        __String* cstr = __String::create(sstr.c_str());
        ret = cstr->getCString();
    }
    return ret;
}

extern "C" {
    // Keyboard イベントの通知
    JNIEXPORT void JNICALL Java_jp_syuhari_RecipeBook_RecipeBook_nativeMyKeyDown(JNIEnv * env, jobject thiz, jint keyCode) {
        __android_log_print(ANDROID_LOG_DEBUG,"KeyDown", "keydown in cocos2dx %d", keyCode);
        
        AppKeyDelegate *delegate = AppPlatform::sharedInstance()->getAppKeyDelegate();
        if (delegate != NULL) {
            delegate->onAppKeyEvent(keyCode);
        }
    }
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

#endif
